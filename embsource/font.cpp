#include "font.h"

namespace embsource
{
    font::font(const std::string &name, unsigned int size, int flags, int weight, int blur,
               int scanlines) : embryo::font::font(name, size)
    {
        m_handle = glob.surface->createFont();

        unsigned int realflags = 0;
        if (flags & embryo::font::italic) realflags |= FONTFLAG_ITALIC;
        if (flags & embryo::font::underline) realflags |= FONTFLAG_UNDERLINE;
        if (flags & embryo::font::strikeout) realflags |= FONTFLAG_STRIKEOUT;
        if (flags & embryo::font::dropshadow) realflags |= FONTFLAG_DROPSHADOW;
        if (flags & embryo::font::outline) realflags |= FONTFLAG_OUTLINE;
        if (flags & embryo::font::antialias) realflags |= FONTFLAG_ANTIALIAS;

        glob.surface->setFontGlyphSet(m_handle, name.c_str(), size, weight, blur, scanlines, realflags);
    }
}