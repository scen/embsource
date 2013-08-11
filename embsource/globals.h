#ifndef embsource_globals_h
#define embsource_globals_h

#include "sdk.h"

#include <libembryo/logger.h>
#include <libembryo/module.h>

class globals
{
public:
    const char *getInterfaceName(embryo::module *mod, const char *prefix);
    CreateInterfaceFn getInterfaceFactory(embryo::module *mod);
    
    CreateInterfaceFn appSysFactory;
    CreateInterfaceFn clientFactory;
    CreateInterfaceFn engineFactory;
    
    void *globalVarsBase;

    void *client;
    void *engine;
    void *cvar;
    void *panel;
    void *ent;
    void *modelRender;
    void *trace;
    void *modelInfo;
    void *surface;
    void *matSystem;
    void *debugOverlay;

    embryo::module *clientMod;
    embryo::module *engineMod;
    embryo::module *matsurfaceMod;
    embryo::module *vgui2Mod;
private:
    bool byteTextCompare(const unsigned char *addr, const char *text);
};

#endif