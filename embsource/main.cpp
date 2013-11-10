#include "sdk.h"
#include "sigs.h"
#include "globals.h"
#include "hooks.h"
#include "render.h"

#include <libembryo/sigscan.h>
#include <libembryo/memmgr.h>

void load() __attribute__((constructor));
void unload() __attribute__((destructor));

namespace embsource
{
    globals glob = {0};
    render rend;
    
    bool getClientDLLInitVars()
    {
        // We retrieve appSysFactory and globalVarsBase
        // They're referenced in engine.dylib -> ClientDLL_Init(void)
        // Both located (in the disasm) at EBX + some_address
        // EBX is loaded from the rel CALL near the beginning that looks like
        // E8 00 00 00 00. This will push the next EIP onto the stack
        // where POP EBX loads the address into EBX
        
        embryo::signature popEBXSig(sigs::popEBXSigStr);
        embryo::sigscan popEBXScan(popEBXSig, *glob.engineMod);
        
        embryo::signature appSysFactorySig(sigs::appSysFactoryStr);
        embryo::sigscan appSysFactoryScan(appSysFactorySig, *glob.engineMod);
        
        unsigned int EBX = (unsigned int)popEBXScan.find();
        
        if (!EBX)
        {
            embryo::log().error("popEbxScan returned NULL");
            return 0;
        }
        
        unsigned char *appSysFactoryRes = (unsigned char *)appSysFactoryScan.find();
        
        if (!appSysFactoryRes)
        {
            embryo::log().error("appSysFactoryScan returned NULL");
            return 0;
        }
        
        glob.appSysFactory = **(CreateInterfaceFn **)(EBX + *(unsigned int *)(appSysFactoryRes + 0x2));
        glob.globalVarsBase = *(void **)(EBX + *(unsigned int *)(appSysFactoryRes + 0x8 + 0x2));
        DUMP_VAR(glob.appSysFactory);
        DUMP_VAR(glob.globalVarsBase);
        
        return glob.appSysFactory != NULL && glob.globalVarsBase != NULL;
    }
    
    void *init(void *__pthreadarg)
    {
        embryo::log().init(embryo::logger::log_stdout | embryo::logger::log_file | embryo::logger::force_flush | embryo::logger::file_color,
                           "/Users/scen/projects/osxinj/bin/Release/debug.log");
        
        glob.clientMod     = new embryo::module("client.dylib");
        glob.engineMod     = new embryo::module("engine.dylib");
        glob.matsurfaceMod = new embryo::module("vguimatsurface.dylib");
        glob.vgui2Mod      = new embryo::module("vgui2.dylib");
        
        auto clientName       = glob.getInterfaceName(glob.clientMod, "VClient0");
        auto engineName       = glob.getInterfaceName(glob.clientMod, "VEngineClient0");
        auto cvarName         = glob.getInterfaceName(glob.clientMod, "VEngineCvar0");
        auto vguiPanelName    = glob.getInterfaceName(glob.clientMod, "VGUI_Panel0");
        auto entName          = glob.getInterfaceName(glob.clientMod, "VClientEntityList0");
        auto modelRenderName  = glob.getInterfaceName(glob.clientMod, "VEngineModel0");
        auto traceName        = glob.getInterfaceName(glob.clientMod, "EngineTraceClient0");
        auto modelInfoName    = glob.getInterfaceName(glob.clientMod, "VModelInfoClient0");
        auto surfaceName      = glob.getInterfaceName(glob.clientMod, "VGUI_Surface0");
        auto matSysName       = glob.getInterfaceName(glob.clientMod, "VMaterialSystem0");
        auto debugOverlayName = glob.getInterfaceName(glob.clientMod, "VDebugOverlay0");
        
        glob.clientFactory = glob.getInterfaceFactory(glob.clientMod);
        glob.engineFactory = glob.getInterfaceFactory(glob.engineMod);
        
        getClientDLLInitVars();
        
        glob.client       = (CHLClient *)glob.clientFactory(clientName, NULL);
        glob.engine       = (CEngineClient *)glob.appSysFactory(engineName, NULL);
        glob.cvar         = glob.appSysFactory(cvarName, NULL);
        glob.panel        = (CPanel *)glob.appSysFactory(vguiPanelName, NULL);
        glob.ent          = glob.clientFactory(entName, NULL);
        glob.modelRender  = glob.appSysFactory(modelRenderName, NULL);
        glob.trace        = glob.appSysFactory(traceName, NULL);
        glob.modelInfo    = glob.appSysFactory(modelInfoName, NULL);
        glob.surface      = (ISurface *)glob.appSysFactory(surfaceName, NULL);
        glob.matSystem    = glob.appSysFactory(matSysName, NULL);
        glob.debugOverlay = glob.engineFactory(debugOverlayName, NULL);
        
        // Retrieve CInput pointer; it's at EAX + some offset
        unsigned int *clientVMT = *(unsigned int **)glob.client;
        
        embryo::sigscan inputBaseScan(embryo::signature("e8 00 00 00 00"), (void *)clientVMT[offsets::IN_ActivateMouse], 0x100);
        unsigned int inputBase = (unsigned int)inputBaseScan.find();
        DUMP_VAR(inputBase);
        if (!inputBase) return NULL;
        
        embryo::sigscan inputOffsetScan(embryo::signature("8b 80"), (void *)clientVMT[offsets::IN_ActivateMouse], 0x100);
        unsigned int inputOffset = (unsigned int)inputOffsetScan.find();
        DUMP_VAR(inputOffset);
        if (!inputOffset) return NULL;
        
        glob.input = (void *)**(unsigned int ***)(inputBase + 0x5 + *(unsigned int *)(inputOffset + 0x2));
        
        DUMP_VAR(glob.client);
        DUMP_VAR(glob.engine);
        DUMP_VAR(glob.cvar);
        DUMP_VAR(glob.panel);
        DUMP_VAR(glob.ent);
        DUMP_VAR(glob.modelRender);
        DUMP_VAR(glob.trace);
        DUMP_VAR(glob.modelInfo);
        DUMP_VAR(glob.surface);
        DUMP_VAR(glob.matSystem);
        DUMP_VAR(glob.debugOverlay);
        DUMP_VAR(glob.input);
        
        rend.init();
        
        glob.nvar = netvar(glob.client);
        glob.nvar.init();
        
        glob.panelHook = new embryo::vmt(glob.panel);
        glob.panelHook->hookMethod((void *)&hooks::hkPaintTraverse, offsets::PaintTraverse);
        
        glob.clientHook = new embryo::vmt(glob.client);
        glob.clientHook->hookMethod((void *)&hooks::hkWriteUsercmdDeltaToBuffer, offsets::WriteUsercmdDeltaToBuffer);
        
        return NULL;
    }
}

void load()
{
    pthread_t thread;
    pthread_create(&thread, NULL, &embsource::init, NULL);
}

void unload()
{
    embsource::glob.clientHook->unhook();
    embsource::glob.clientHook->poof();
    embsource::glob.panelHook->unhook();
    embsource::glob.panelHook->poof();
    
    embryo::log().warn("unloading module");
}