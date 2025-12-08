
#include "../headers/includes.h"

_am_bool is_command(char *input, char *command) { return strcmp(input, command) == 0 ? _AM_TRUE : _AM_FALSE; }

t_alloc *alloc_exists(t_alloc **allocs, void *alloc)
{
    allocs_iterator it = *allocs;
    while (it != NULL)
    {
        if (alloc == it->_alloc)
            return it;
        it = it->_next;
    }
    return NULL;
}

t_fd *fd_exists(t_fd **fds, int fd)
{
    fds_iterator it = *fds;
    while (it != NULL)
    {
        if (fd == it->_fd)
            return it;
        it = it->_next;
    }
    return NULL;
}
