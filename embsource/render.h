#ifndef embsource_render_h
#define embsource_render_h

#include <libembryo/render.h>

#include "globals.h"
#include "font.h"

namespace embsource
{
    class render : public embryo::render<int>
    {
    public:
        void init();

        virtual embryo::size<int> drawText(const embryo::point<int> &p, const embryo::font &fnt, const embryo::color &col, const std::string &str);
        virtual embryo::size<int> measureText(const embryo::font &fnt, const std::string &str);
        virtual void drawLine(const embryo::point<int> &begin, const embryo::point<int> &end, const embryo::color &col);

        virtual void fillRect(const embryo::rect<int> &r, const embryo::color &col);
        virtual void outlineRect(const embryo::rect<int> &r, const embryo::color &col);

        font uiFont;
    };

    extern globals glob;
}

#endif