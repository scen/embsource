#include "globals.h"

bool globals::byteTextCompare(const unsigned char *addr, const char *text)
{
    for (; *text; ++addr, ++text)
    {
        if (*addr != (unsigned char)*text)
            return false;
    }
    return true;
}

const char *globals::getInterfaceName(embryo::module *mod, const char *prefix)
{
    for (int i = 0; i < mod->size(); i++)
    {
        if (byteTextCompare((unsigned char *)mod->start() + i, prefix))
        {
            embryo::log().verb(format("interface version: %s") % std::string((char *)mod->start() + i));
            return (const char *)mod->start() + i;
        }
    }
    embryo::log().error(format("could not find interface for prefix: %s") % prefix);
    return NULL;
}

CreateInterfaceFn globals::getInterfaceFactory(embryo::module *mod)
{
    CreateInterfaceFn fn = mod->getSymbol<CreateInterfaceFn>("CreateInterface");
    embryo::log().verb(format("%s CreateInterfaceFn: %X") % mod->name() % (void *)fn);
    return fn;
}