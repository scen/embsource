#ifndef embsource_offsets_h
#define embsource_offsets_h

namespace embsource
{
    namespace offsets
    {
        #define ofst const unsigned int

        // IPanel
        ofst PaintTraverse             = 42;
        ofst GetPanelName              = 37;

        // ISurface
        ofst CreateFont                = 66;
        ofst SetFontGlyphSet           = 67;
        ofst DrawSetColor              = 10;
        ofst DrawFilledRect            = 12;
        ofst DrawOutlinedRect          = 14;
        ofst DrawLine                  = 15;
        ofst DrawSetTextColor          = 18;
        ofst DrawSetTextFont           = 17;
        ofst DrawSetTextPos            = 20;
        ofst DrawPrintText             = 22;
        ofst GetTextSize               = 75;
        
        // CHLClient
        ofst CreateMove                = 21;
        ofst WriteUsercmdDeltaToBuffer = 23;
        ofst IN_ActivateMouse          = 14;
        ofst GetAllClasses             = 8;

        // CEngineClient
        ofst GetScreenSize             = 5;
        ofst GetPlayerInfo             = 8;
        ofst Con_IsVisible             = 11;
        ofst GetLocalPlayer            = 12;
        ofst Time                      = 14;
        ofst GetViewAngles             = 19;
        ofst SetViewAngles             = 20;
        ofst GetMaxClients             = 21;
        ofst IsInGame                  = 26;
        ofst IsConnected               = 27;
        ofst IsDrawingLoadingImage     = 28;
        ofst WorldToScreenMatrix       = 36;
        ofst IsTakingScreenshot        = 85;
        ofst GetNetChannelInfo         = 72;
        ofst ClientCmd_Unrestricted    = 106;
        
        // CClientEntityList
        ofst GetClientEntity           = 5;
        ofst GetClientEntityFromHandle = 9;
        ofst GetHighestEntityIndex     = 10;

        // CBaseEntity
        ofst GetAbsOrigin              = 11;

        #undef ofst
    }
}

#endif