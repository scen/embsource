#ifndef embsource_sigs_h
#define embsource_sigs_h

namespace embsource
{
    namespace sigs
    {
//        static const char *popEBXSigStr = "5b 8b 83 ? ? ? ? 89 85 ? ? ? ? 8b 00 89 45 ? e8 ? ? ? ? 81 bb ? ? ? ? ? ? ? ? 0f 84 ? ? ? ? 8d 83 ? ? ? ? 89 04 24";
        static const char *popEBXSigStr = "89 74 24 0c 89 54 24 08 89 54 24 04 89 04 24 ff 11 85 c0 75 0e";
        static const char *appSysFactoryStr = "8b 93 ? ? ? ? 8b 12 8b b3 ? ? ? ? 89 74 24";
    }
}

#endif