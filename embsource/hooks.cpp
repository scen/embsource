#include "hooks.h"

#include <libembryo/logger.h>

namespace embsource
{
    void hooks::hkPaintTraverse(void *thisptr, unsigned int panel, bool forceRepaint, bool allowForce)
    {
        glob.panelHook->unhookMethod(offsets::PaintTraverse);
        glob.panelHook->getMethod<PaintTraverse_t>(offsets::PaintTraverse)(thisptr, panel, forceRepaint, allowForce);
        glob.panelHook->hookMethod((void *)&hkPaintTraverse, offsets::PaintTraverse);
        
        if (!glob.panelDraw)
        {
            DUMP_VAR(thisptr);
            const char *panelName = glob.panel->getPanelName(panel);
            if (panelName[0] == 'F' && panelName[5] == 'O' && panelName[12] == 'P')
            {
                glob.panelDraw = panel;
                DUMP_VAR(glob.panelDraw);
            }
        }

        if (panel == glob.panelDraw)
        {
            
        }
    }
    
    bool hooks::hkWriteUsercmdDeltaToBuffer(void *thisptr, unsigned int *buf, int from, int to, bool isnewcommand)
    {
        
    }
}