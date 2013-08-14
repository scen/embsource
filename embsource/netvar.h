#ifndef embsource_netvar_h
#define embsource_netvar_h

#include "sdk.h"

#include <libembryo/logger.h>

#include <string>
#include <map>

namespace embsource
{
    class netvar
    {
    public:
        netvar() {}
        netvar(CHLClient *client) : client(client) {}

        void init();

        RecvTable *findTable(const std::string &str);
        RecvProp *findProp(RecvTable *pRecvTable, const std::string &str, int *x);
        unsigned int findOffset(RecvTable *pRecvTable, const std::string &str);
        unsigned int get(const std::string &str) const;
        unsigned int operator[](const std::string &str) const;
        void dump();
        void helper(RecvTable *table, const std::string &parent = "");

        // Offsets for TF2
        unsigned int ply_Class, ply_LifeState, ply_Health, ply_TfCond,
            ply_ActiveWeapon, ply_Weapons, ply_GlowEnabled, ply_Shared, ply_medigunCharge, ply_EyePos,
            ply_EyeAngles1;
        unsigned int spy_DTeam, spy_DClass, spy_Backstab;
        unsigned int obj_Level, obj_Builder, obj_Health, obj_Sapper, obj_Mini, obj_MaxHealth, obj_Metal,
            obj_Building, obj_Mode, obj_Disabled, obj_Percent;
        unsigned int sentry_Wrangle, sentry_Shield, sentry_Rockets, sentry_Shells;
        unsigned int ent_Team;
        unsigned int off_AttributeManager, off_item, off_ItemDefIdx;
        unsigned int wep_lastFireTime, wep_lastCritCheckTime, wep_ammoType;
        unsigned int bomb_Type, bomb_Touched, bomb_Owner, bomb_Critical;

        CHLClient *client;

        std::map<std::string, unsigned int> offsets;
    };
}

#endif