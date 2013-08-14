#ifndef embsource_sdk_h
#define embsource_sdk_h

#include <libembryo/memhelp.h>
#include <libembryo/logger.h>
#include <libembryo/mathlib.h>

#include "offsets.h"

#include "source_sdk/dt_recv.h"

#define DUMP_VAR(x) embryo::log().verb(format("%-25s: %X") % (#x) % (void *)x)

namespace embsource
{
    typedef void *(*CreateInterfaceFn)(const char *name, int *retCode);
    typedef void(*PaintTraverse_t)(void *, unsigned int, bool, bool);
    
    typedef float matrix3x4[3][4];
    
    typedef struct player_info_s
    {
        char			name[32];
        int				userID;
        char			guid[33];
        unsigned long	friendsID;
        char			friendsName[32];
        bool			fakeplayer;
        bool			ishltv;
        unsigned long	customFiles[4];
        unsigned char	filesDownloaded;
    } player_info_t;
    
    // Forward declarations
    class ISurface;
    class Vector;
    class CEntityList;
    class CBaseEntity;
    class CEngineClient;
    class CPanel;
    class ClientClass;
    class CHLClient;

    class CHLClient
    {
    public:
        ClientClass* getAllClasses()
        {
            typedef ClientClass *(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, offsets::GetAllClasses)(this);
        }
    };
    
    class ClientClass
    {
    public:
        const char *name() const { return *(const char **)(this + 0x8); }
        RecvTable *table() const { return *(RecvTable **)(this + 0xC); }
        ClientClass *next() const { return *(ClientClass **)(this + 0x10); }
        int classID() const { return *(int *)(this + 0x14); }
    };
    
    class CPanel
    {
    public:
        const char *getPanelName(unsigned int panel)
        {
            typedef const char *(*OrigFn_t)(void *, unsigned int);
            return embryo::getvfunc<OrigFn_t>(this, offsets::GetPanelName)(this, panel);
        }
    };
    
    class Vector
    {
    public:
        float x, y, z;
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
    
    class CEngineClient
    {
    public:
        void getScreenSize(int& width, int& height)
        {
            typedef void(*OrigFn_t)(void *, int& , int&);
            return embryo::getvfunc<OrigFn_t>(this, 5)(this, width, height);
        }
        
        bool getPlayerInfo(int ent_num, player_info_t *pinfo)
        {
            typedef bool(*OrigFn_t)(void *, int, player_info_t *);
            return embryo::getvfunc<OrigFn_t>(this, 8)(this, ent_num, pinfo);
        }
        
        bool Con_IsVisible()
        {
            typedef bool(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, 11)(this);
        }
        
        int getLocalPlayer()
        {
            typedef int(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, 12)(this);
        }
        
        float time()
        {
            typedef float(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, 14)(this);
        }
        
        void getViewAngles(embryo::vector3& va)
        {
            typedef void(*OrigFn_t)(void *, Vector& va);
            return embryo::getvfunc<OrigFn_t>(this, 19)(this, *(Vector *)&va);
        }
        
        void setViewAngles(embryo::vector3& va)
        {
            typedef void(*OrigFn_t)(void *, Vector& va);
            return embryo::getvfunc<OrigFn_t>(this, 20)(this, *(Vector *)&va);
        }
        
        int getMaxClients()
        {
            typedef int(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, 21)(this);
        }
        
        bool isInGame()
        {
            typedef bool(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, 26)(this);
        }
        
        bool isConnected()
        {
            typedef bool(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, 27)(this);
        }
        
        bool isDrawingLoadingImage()
        {
            typedef bool(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, 28)(this);
        }
        
        const matrix3x4& worldToScreenMatrix()
        {
            typedef const matrix3x4&(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, 36)(this);
        }
        
        bool isTakingScreenshot()
        {
            typedef bool(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, 85)(this);
        }
        
        unsigned int* getNetChannelInfo()
        {
            typedef unsigned int*(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, 72)(this);
        }
        
        void clientCmd_Unrestricted(const char* cmd)
        {
            typedef void(*OrigFn_t)(void *, const char *);
            return embryo::getvfunc<OrigFn_t>(this, 106)(this, cmd);
        }
    };
    
    class CEntityList
    {
    public:
        CBaseEntity *getClientEntity(int entnum)
        {
            typedef CBaseEntity *(*OrigFn_t)(void *, int);
            return embryo::getvfunc<OrigFn_t>(this, offsets::GetClientEntity)(this, entnum);
        }
        
        CBaseEntity *getClientEntityFromHandle(unsigned int handle)
        {
            typedef CBaseEntity *(*OrigFn_t)(void *, unsigned int);
            return embryo::getvfunc<OrigFn_t>(this, offsets::GetClientEntityFromHandle)(this, handle);
        }
        
        int getHighestEntityIndex()
        {
            typedef int(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, offsets::GetHighestEntityIndex)(this);
        }
    };
    
    class CBaseEntity
    {
    public:
        embryo::vector3 getAbsOrigin()
        {
            typedef embryo::vector3(*OrigFn_t)(void *);
            return embryo::getvfunc<OrigFn_t>(this, offsets::GetAbsOrigin)(this);
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
        FONTFLAG_CUSTOM         = 0x400,
    };
}

#endif