#ifndef embsource_font_h
#define embsource_font_h

#include <libembryo/font.h>

#include "globals.h"

namespace embsource
{
    class font : public embryo::font
    {
    public:
        font() {}
        font(const std::string &name, unsigned int size, int flags = embryo::font::none, int weight = 500, int blur = 0,
            int scanlines = 0);
        
        unsigned int handle() const { return m_handle; }
    protected:
        unsigned int m_handle;
    };
    
    extern globals glob;
}

#endif