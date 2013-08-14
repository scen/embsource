#include "render.h"

#include "globals.h"

#include <wchar.h>

#include <libembryo/logger.h>

namespace embsource
{
    extern globals glob;
    
    void render::init()
    {
        glob.engine->getScreenSize(screen.w(), screen.h());
        embryo::log().verb(format("screen: %ux%u") % screen.w() % screen.h());
        
        uiFont = font("Tahoma", 13, embryo::font::outline | embryo::font::antialias, 800);
    }
    
    embryo::size<int> render::drawText(const embryo::point<int> &p, const embryo::font &fnt, const embryo::color &col, const std::string &str)
    {
        auto sf = reinterpret_cast<const font&>(fnt);
        
        wchar_t wstr[1024];
        mbstowcs(wstr, str.c_str(), str.length());
        
        glob.surface->drawSetTextColor(col.r(), col.g(), col.b(), col.a());
        glob.surface->drawSetTextFont(sf.handle());
        glob.surface->drawSetTextPos(p.x(), p.y());
        glob.surface->drawPrintText(wstr, str.length());
        
        embryo::size<int> ret;
        glob.surface->getTextSize(sf.handle(), wstr, ret.w(), ret.h());
        return ret;
    }

    embryo::size<int> render::measureText(const embryo::font &fnt, const std::string &str)
    {
        auto sf = reinterpret_cast<const font&>(fnt);
        
        wchar_t wstr[1024];
        mbstowcs(wstr, str.c_str(), str.length());
        
        embryo::size<int> ret;
        glob.surface->getTextSize(sf.handle(), wstr, ret.w(), ret.h());
        return ret;
    }

    void render::drawLine(const embryo::point<int> &begin, const embryo::point<int> &end, const embryo::color &col)
    {
        glob.surface->drawSetColor(col.r(), col.g(), col.b(), col.a());
        glob.surface->drawLine(begin.x(), begin.y(), end.x(), end.y());
    }

    void render::fillRect(const embryo::rect<int> &r, const embryo::color &col)
    {
        glob.surface->drawSetColor(col.r(), col.g(), col.b(), col.a());
        glob.surface->drawFilledRect(r.pos().x(), r.pos().y(), r.pos().x() + r.size().w(), r.pos().y() + r.size().h());
    }

    void render::outlineRect(const embryo::rect<int> &r, const embryo::color &col)
    {
        glob.surface->drawSetColor(col.r(), col.g(), col.b(), col.a());
        glob.surface->drawOutlinedRect(r.pos().x(), r.pos().y(), r.pos().x() + r.size().w(), r.pos().y() + r.size().h());
    }
}