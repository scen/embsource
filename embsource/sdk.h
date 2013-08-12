#ifndef embsource_sdk_h
#define embsource_sdk_h

#include <libembryo/memhelp.h>
#include <libembryo/logger.h>

#include "offsets.h"

#define DUMP_VAR(x) embryo::log().verb(format("%-25s: %X") % (#x) % (void *)x)

namespace embsource
{
    typedef void *(*CreateInterfaceFn)(const char *name, int *retCode);
    typedef void(*PaintTraverse_t)(void *, unsigned int, bool, bool);

    class CPanel
    {
    public:
        const char *getPanelName(unsigned int panel)
        {
            typedef const char *(*OrigFn_t)(void *, unsigned int);
            return embryo::getvfunc<OrigFn_t>(this, offsets::GetPanelName)(this, panel);
        }
    };

    class ISurface
    {
    public:
        unsigned int createFont()
        {
            typedef unsigned int(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, offsets::CreateFont)(this);
        }

        void setFontGlyphSet(unsigned int handle, const char *name, int tall, int weight, int blur, int scanlines, int flags)
        {
            typedef void(*OrigFn_t)(void *, unsigned int, const char *, int, int, int, int, int, int, int);
            return embryo::getvfunc<OrigFn_t>(this, offsets::SetFontGlyphSet)(this, handle, name, tall, weight, blur, scanlines, flags, 0, 0);
        }

        void drawSetTextFont(unsigned int handle)
        {
            typedef void(*OrigFn_t)(void *, unsigned int);
            return embryo::getvfunc<OrigFn_t>(this, offsets::DrawSetTextFont)(this, handle);
        }

        void drawSetTextColor(int r, int g, int b, int a)
        {
            typedef void(*OrigFn_t)(void *, int, int, int, int);
            return embryo::getvfunc<OrigFn_t>(this, offsets::DrawSetTextColor)(this, r, g, b, a);
        }

        void drawSetTextPos(int x, int y)
        {
            typedef void(*OrigFn_t)(void *, int, int);
            return embryo::getvfunc<OrigFn_t>(this, offsets::DrawSetTextPos)(this, x, y);
        }

        void drawPrintText(const wchar_t *text, int len)
        {
            typedef void(*OrigFn_t)(void *, const wchar_t *, int);
            return embryo::getvfunc<OrigFn_t>(this, offsets::DrawPrintText)(this, text, len);
        }

        void drawSetColor(int r, int g, int b, int a)
        {
            typedef void(*OrigFn_t)(void *, int, int, int, int);
            return embryo::getvfunc<OrigFn_t>(this, offsets::DrawSetColor)(this, r, g, b, a);
        }

        void drawFilledRect(int x0, int y0, int x1, int y1)
        {
            typedef void(*OrigFn_t)(void *, int, int, int, int);
            return embryo::getvfunc<OrigFn_t>(this, offsets::DrawFilledRect)(this, x0, y0, x1, y1);
        }

        void drawOutlinedRect(int x0, int y0, int x1, int y1)
        {
            typedef void(*OrigFn_t)(void *, int, int, int, int);
            return embryo::getvfunc<OrigFn_t>(this, offsets::DrawOutlinedRect)(this, x0, y0, x1, y1);
        }

        void drawLine(int x0, int y0, int x1, int y1)
        {
            typedef void(*OrigFn_t)(void *, int, int, int, int);
            return embryo::getvfunc<OrigFn_t>(this, offsets::DrawLine)(this, x0, y0, x1, y1);
        }
        
        void getTextSize(unsigned int handle, const wchar_t *text, int &width, int &height)
        {
            typedef void(*OrigFn_t)(void *, unsigned int, const wchar_t *, int &, int &);
            return embryo::getvfunc<OrigFn_t>(this, offsets::GetTextSize)(this, handle, text, width, height);
        }
    };

    enum Source_fontflags
    {
        FONTFLAG_NONE,
        FONTFLAG_ITALIC         = 0x001,
        FONTFLAG_UNDERLINE      = 0x002,
        FONTFLAG_STRIKEOUT      = 0x004,
        FONTFLAG_SYMBOL         = 0x008,
        FONTFLAG_ANTIALIAS      = 0x010,
        FONTFLAG_GAUSSIANBLUR   = 0x020,
        FONTFLAG_ROTARY         = 0x040,
        FONTFLAG_DROPSHADOW     = 0x080,
        FONTFLAG_ADDITIVE       = 0x100,
        FONTFLAG_OUTLINE        = 0x200,
        FONTFLAG_CUSTOM         = 0x400,    // custom generated font -
    };
}

#endif