
#include "access_mem.h"

void print_mem_handler(t_alloc *allocs)
{
    if (!allocs) { printf("[%s]: No memory was allocated yet\n", DEFAULT_LOG); return; }

    allocs_iterator iterator = allocs;
    printf("[%s]: Currently allocated memory:\n", DEFAULT_LOG);
    while (iterator != NULL)
    {
        printf("-> %p\n", iterator->_alloc);
        iterator = iterator->_next;
    }
}

void nuke_handler() { access_mem_CLOSE_ALL(); access_mem_FREE_ALL(); printf("[%s]: Your environment was nuked succefully 💥\n", DEFAULT_LOG); exit(NUKE_EXIT_CODE); }