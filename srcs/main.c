
#include "access_mem.h"

int main()
{
    access_mem_PRINT_MEM();
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    char *dsadsa = access_mem_ALLOC(100);
    dsadsa = access_mem_ALLOC(100);
    dsadsa = access_mem_ALLOC(100);
    dsadsa = access_mem_ALLOC(100);
    dsadsa = access_mem_ALLOC(100);
    dsadsa = access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_ALLOC(100);
    access_mem_PRINT_MEM();
    access_mem_FREE_ALLOC(dsadsa);
    char *dsa = access_mem_ALLOC(100);
    dsa = access_mem_ALLOC(100);
    char *dsaa = access_mem_ALLOC(100);
    dsa = access_mem_ALLOC(100);
    dsa = access_mem_ALLOC(100);
    access_mem_PRINT_MEM();
    access_mem_FREE_ALLOC(dsaa);
    access_mem_PRINT_MEM();
    access_mem_FREE_ALLOC(dsa);
    access_mem_PRINT_MEM();
    access_mem_FREE_ALLOC(dsa);
    access_mem_FREE_ALLOC(dsaa);

    int fd = access_mem_OPEN("./makefile", O_RDONLY);
    access_mem_OPEN("./makefile", O_RDONLY, 0765);
    access_mem_OPEN("./testttt", O_CREAT, 0000, 7865765);
    access_mem_OPEN("./makefile", O_RDONLY);
    fd = access_mem_OPEN("", O_RDONLY);
    access_mem_CLOSE_FD(fd);
    access_mem_CLOSE_FD(-1);
    // access_mem_CLOSE_ALL();

    char *tt = malloc(100);
    access_mem_FREE_ALLOC(tt);
    access_mem_NUKE();
}