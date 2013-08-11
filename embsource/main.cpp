#include "sdk.h"
#include "globals.h"

#include <libembryo/sigscan.h>

#define DUMP_VAR(x) embryo::log().verb(format("%-25s: %X") % (#x) % (void *)x)

void init() __attribute__((constructor));
void uninit() __attribute__((destructor));

globals *glob;

void init()
{
    embryo::log().init(embryo::logger::log_stdout | embryo::logger::log_file | embryo::logger::force_flush | embryo::logger::file_color,
                       "/Users/scen/projects/osxinj/bin/Release/debug.log");
    
    glob = new globals;

    glob->clientMod     = new embryo::module("client.dylib");
    glob->engineMod     = new embryo::module("engine.dylib");
    glob->matsurfaceMod = new embryo::module("vguimatsurface.dylib");
    glob->vgui2Mod      = new embryo::module("vgui2.dylib");

    // ClientDLL_Init()
    // embryo::signature clientInitSig("8b 93 ? ? ? ? 8b 12 8b b3 ? ? ? ? 89 74 24");
    embryo::signature clientInitSig("8b 93 ? ? ? ? 8b 12 8b b3 ? ? ? ? 89 74 24 ? 89 54 24 ? 89 54 24 ? 89 0c 24 ff 10 85 c0 75 ? 8d 83 ? ? ? ? 89 04 24 e8");
    embryo::sigscan clientInitScan(clientInitSig, *glob->engineMod);
    unsigned char *clientInitRes = (unsigned char *)clientInitScan.find();

    if (!clientInitRes)
    {
        embryo::log().error("clientInitScan returned NULL");
        return;
    }
    
    auto clientName       = glob->getInterfaceName(glob->clientMod, "VClient0");
    auto engineName       = glob->getInterfaceName(glob->clientMod, "VEngineClient0");
    auto cvarName         = glob->getInterfaceName(glob->clientMod, "VEngineCvar0");
    auto vguiPanelName    = glob->getInterfaceName(glob->clientMod, "VGUI_Panel0");
    auto entName          = glob->getInterfaceName(glob->clientMod, "VClientEntityList0");
    auto modelRenderName  = glob->getInterfaceName(glob->clientMod, "VEngineModel0");
    auto traceName        = glob->getInterfaceName(glob->clientMod, "EngineTraceClient0");
    auto modelInfoName    = glob->getInterfaceName(glob->clientMod, "VModelInfoClient0");
    auto surfaceName      = glob->getInterfaceName(glob->clientMod, "VGUI_Surface0");
    auto matSysName       = glob->getInterfaceName(glob->clientMod, "VMaterialSystem0");
    auto debugOverlayName = glob->getInterfaceName(glob->clientMod, "VDebugOverlay0");
    
    glob->clientFactory = glob->getInterfaceFactory(glob->clientMod);
    glob->engineFactory = glob->getInterfaceFactory(glob->engineMod);
    glob->appSysFactory = **(CreateInterfaceFn **)(clientInitRes + 0x2);
    DUMP_VAR(glob->appSysFactory);

    glob->client       = glob->clientFactory(clientName, NULL);
//    glob->engine       = glob->appSysFactory(engineName, NULL);
//    glob->cvar         = glob->appSysFactory(cvarName, NULL);
//    glob->panel        = glob->appSysFactory(vguiPanelName, NULL);
    glob->ent          = glob->clientFactory(entName, NULL);
//    glob->modelRender  = glob->appSysFactory(modelRenderName, NULL);
//    glob->trace        = glob->appSysFactory(traceName, NULL);
//    glob->modelInfo    = glob->appSysFactory(modelInfoName, NULL);
//    glob->surface      = glob->appSysFactory(surfaceName, NULL);
//    glob->matSystem    = glob->appSysFactory(matSysName, NULL);
    glob->debugOverlay = glob->engineFactory(debugOverlayName, NULL);

    DUMP_VAR(glob->client);
    DUMP_VAR(glob->engine);
    DUMP_VAR(glob->cvar);
    DUMP_VAR(glob->panel);
    DUMP_VAR(glob->ent);
    DUMP_VAR(glob->modelRender);
    DUMP_VAR(glob->trace);
    DUMP_VAR(glob->modelInfo);
    DUMP_VAR(glob->surface);
    DUMP_VAR(glob->matSystem);
    DUMP_VAR(glob->debugOverlay);

    glob->globalVarsBase = *(unsigned char **)(clientInitRes + 0xA);
    DUMP_VAR(glob->globalVarsBase);
}

void uninit()
{
    embryo::log().info("unloading module");
}