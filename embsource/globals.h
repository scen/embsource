#ifndef embsource_globals_h
#define embsource_globals_h

#include "sdk.h"

#include "offsets.h"

#include <libembryo/logger.h>
#include <libembryo/module.h>
#include <libembryo/vmt.h>

namespace embsource
{
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
        CPanel *panel;
        void *ent;
        void *modelRender;
        void *trace;
        void *modelInfo;
        ISurface *surface;
        void *matSystem;
        void *debugOverlay;

        embryo::module *clientMod;
        embryo::module *engineMod;
        embryo::module *matsurfaceMod;
        embryo::module *vgui2Mod;
        
        embryo::vmt *panelHook;
        embryo::vmt *clientHook;

        unsigned int panelDraw;
    private:
        bool byteTextCompare(const unsigned char *addr, const char *text);
    };
}

#endif