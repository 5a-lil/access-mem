
#include "access_mem.h"

void *open_handler(t_fd **fds, va_list options)
{
    static t_fd *last_fd = NULL;
    
    const char *pathname = va_arg(options, const char *);
    int flags = va_arg(options, int);
    
    int new_fd = -1;
    if (flags & O_CREAT) { mode_t mode = va_arg(options, mode_t); new_fd = open(pathname, flags, mode); } // open the file in the path given as arg with mode arg in addition
    else new_fd = open(pathname, flags); // open the file in the path given as arg
    if (new_fd < 0) { printf("[%s]: Opening file at path [\"%s\"] failed\n", ERROR_LOG, pathname); return OPEN_SERIALIZE -1; } // if failure we return -1 in case the file just doesnt exist

    t_fd *new_node = malloc(sizeof(t_fd));
    if (!new_node) { close(new_fd); last_fd = NULL; access_mem_NUKE(); return MALLOC_FAILED; } // if failure we should FREE ALL and exit and close also all fds
    new_node->_fd = new_fd;
    new_node->_next = NULL;

    if (!(*fds)) return *fds = new_node, last_fd = new_node, OPEN_SERIALIZE new_fd; // if the list is empty add the malloc to the head;
    return last_fd->_next = new_node, last_fd = new_node, OPEN_SERIALIZE new_fd;
}

void close_fd_handler(t_fd **fds, int fd_to_close)
{
    // if fds list is empty
    if (!(*fds)) { printf("[%s]: File descriptor [%d] doesn't exist\n", BOLD_YELLOW, fd_to_close); return; }
    
    // if the deleted node is head
    if ((*fds)->_fd == fd_to_close)
    {
        t_fd *new_head = (*fds)->_next;
        close((*fds)->_fd);
        free(*fds);
        *fds = new_head;
        return;
    }

    // if the deleted node is in the middle
    fds_iterator iterator = *fds;
    t_fd *previous = NULL;
    while (iterator != NULL)
    {
        if (iterator->_fd == fd_to_close)
        {
            previous->_next = iterator->_next;
            close(iterator->_fd);
            free(iterator);
            return;
        }
        previous = iterator;
        iterator = iterator->_next;
    }

    // nothing was found
    printf("[%s]: File descriptor [%d] doesn't exist\n", WARNING_LOG, fd_to_close);
}

void close_all_handler(t_fd **fds) { while ((*fds) != NULL) access_mem_CLOSE_FD((*fds)->_fd); }