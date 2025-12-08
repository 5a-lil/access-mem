
#include "includes.h"

void log_mem_handler(t_alloc *allocs)
{
    if (!allocs) { printf("[%s]: No memory was allocated yet\n", DEFAULT_LOG); return; }

    allocs_iterator iterator = allocs;
    printf("[%s]: Currently allocated memory:\n", DEFAULT_LOG);
    while (iterator != NULL)
    {
        MEM_LOG();
        iterator = iterator->_next;
    }
}

void nuke_handler(t_alloc **allocs, t_fd **fds, va_list options) 
{ 
    /* access_mem_CLOSE_ALL(); */
    NUKE_START_DEBUG_LOG(); 
    
    void *previous_free = NULL;
    while ((*allocs) != NULL) 
    {
        t_alloc *new_head = (*allocs)->_next;
        if ((*allocs)->_alloc == previous_free) // in case there is two times the same alloc registered
        {
            free(*allocs);
            *allocs = new_head; // MAYBE USELESS because of double register already handled
            // so no dupes possible
            continue;
        }
        previous_free = (*allocs)->_alloc;
        FREE_ALL_DEBUG_LOG();
        free((*allocs)->_alloc);
        free(*allocs);
        *allocs = new_head;
    }

    int previous_close = -1;
    while ((*fds) != NULL) 
    {
        t_fd *new_head = (*fds)->_next;
        if ((*fds)->_fd == previous_close) // in case there is two times the same alloc registered
        {
            free(*fds);
            *fds = new_head; // MAYBE USELESS because of double register already handled
            // so no dupes possible
            continue;
        }
        previous_close = (*fds)->_fd;
        CLOSE_ALL_DEBUG_LOG();
        close((*fds)->_fd);
        free(*fds);
        *fds = new_head;
    }
    
    NUKE_SUCCESS_DEBUG_LOG(); 
    if (va_arg(options, _am_va_arg_bool) == _AM_EXIT_ON)
        exit(va_arg(options, int)); 
}