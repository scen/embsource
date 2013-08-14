#ifndef embsource_hooks_h
#define embsource_hooks_h

#include "sdk.h"
#include "globals.h"
#include "render.h"

namespace embsource
{
    class hooks
    {
    public:
        static void hkPaintTraverse(void *thisptr, unsigned int panel, bool forceRepaint, bool allowForce);
        static bool hkWriteUsercmdDeltaToBuffer(void *thisptr, unsigned int *buf, int from, int to, bool isnewcommand);
    };

    extern globals glob;
    extern render rend;
}



#endif