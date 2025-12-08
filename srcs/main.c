
#include "../access_mem.h"

void *nimp(int size)
{
    return _AM_MALLOC(size);
}

int main()
{
    char ***temp = nimp(77);
    _AM_LOG_MEM();
    char **temp2 = nimp(11);
    _AM_OPEN("./Makefile", O_WRONLY);
    _AM_REGISTER_FD(_AM_OPEN("./Makefile", O_WRONLY));
    _AM_LOG_MEM();
    _AM_FREE(temp);
    _AM_FREE(temp);
    _AM_FREE(temp2);
    _AM_FREE(temp2);
    _AM_LOG_MEM();
    _AM_REGISTER_ALLOC(malloc(7));
    _AM_NUKE_NO_EXIT();
}