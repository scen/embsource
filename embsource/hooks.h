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
    };

    extern globals glob;
    extern render rend;
}



#endif