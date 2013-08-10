#include <libembryo/logger.h>
#include <libembryo/module.h>
#include <libembryo/sigscan.h>

void init() __attribute__((constructor));

typedef void *(*CreateInterfaceFn)(const char *name, int *retCode);

embryo::module *clientMod, *engineMod;

bool byteTextCompare(const unsigned char *addr, const char *text)
{
    for (; *text; ++addr, ++text)
    {
        if (*addr != (unsigned char)*text)
            return false;
    }
    return true;
}

const char *getInterfaceName(embryo::module *mod, const char *prefix)
{
    for (int i = 0; i < mod->size(); i++)
    {
        if (byteTextCompare((unsigned char *)mod->start() + i, prefix))
        {
            embryo::log().info(format("interface version: %s") % std::string((char *)mod->start() + i));
            return (const char *)mod->start() + i;
        }
    }
    embryo::log().error(format("could not find interface for prefix: %s") % prefix);
    return NULL;
}

CreateInterfaceFn getInterfaceFactory(embryo::module *mod)
{
    CreateInterfaceFn fn = mod->getSymbol<CreateInterfaceFn>("CreateInterface");
    embryo::log().verb(format("%s CreateInterfaceFn: %X") % mod->name() % (void *)fn);
    return fn;
}

void init()
{
    embryo::log().init(embryo::logger::log_stdout | embryo::logger::log_file | embryo::logger::force_flush | embryo::logger::file_color,
                       "/Users/scen/projects/osxinj/bin/Release/debug.log");
    
    clientMod = new embryo::module("client.dylib");
    engineMod = new embryo::module("engine.dylib");
    
    auto clientName = getInterfaceName(clientMod, "VClient0");
    auto vguiPanelName = getInterfaceName(clientMod, "VGUI_Panel0");
    
    auto clientInterfaceFactory = getInterfaceFactory(clientMod);
    void *gClient = clientInterfaceFactory(clientName, NULL);
    
    embryo::signature clientInitSig("8b 93 ? ? ? ? 8b 12 8b b3 ? ? ? ? 89 74 24");
    embryo::sigscan clientInitScan(clientInitSig, *engineMod);
    unsigned char *clientInitRes = (unsigned char *)clientInitScan.find();

    if (!clientInitRes)
    {
        embryo::log().error("clientInitScan returned NULL");
        return;
    }

    void *appSysFactory = *(unsigned char **)(clientInitRes + 0x2);
    void *clientGlobals = *(unsigned char **)(clientInitRes + 0xA);

    embryo::log().info(format("appSysFactory = %X clientGlobals = %X") % appSysFactory % clientGlobals);
}