
#include "includes.h"

void *open_handler(t_fd **fds, t_fd **last_fd, va_list options)
{
    const char *pathname = va_arg(options, const char *);
    int flags = va_arg(options, int);
    open_pos open_origin = va_arg(options, open_pos);
    
    int new_fd = -1;
    // open the file in the path given as arg with mode arg in addition
    if (flags & O_CREAT) { mode_t mode = va_arg(options, mode_t); new_fd = open(pathname, flags, mode); }
    else new_fd = open(pathname, flags); // open the file in the path given as arg
    // if failure we return -1 in case the file just doesnt exist
    if (new_fd < 0) { OPEN_FAIL_DEBUG_LOG(); return OPEN_SERIALIZE -1; }

    t_fd *new_node = malloc(sizeof(t_fd));
    if (!new_node) { close(new_fd); OPEN_FAIL_DEBUG_LOG(); MALLOC_FAILED(); } // if failure we should FREE ALL and exit and close also all fds
    new_node->_fd = new_fd;
    new_node->_open_pos = open_origin;
    new_node->_next = NULL;

    OPEN_SUCCESS_DEBUG_LOG();
    if (!(*fds)) return *fds = new_node, *last_fd = new_node, OPEN_SERIALIZE new_fd; // if the list is empty add the malloc to the head;
    return (*last_fd)->_next = new_node, *last_fd = new_node, OPEN_SERIALIZE new_fd;
}

void close_handler(t_fd **fds, t_fd **last_fd, va_list options)
{
    int fd_to_close = va_arg(options, int);

    // if fds list is empty
    if (!(*fds)) { CLOSE_FAIL_DEBUG_LOG(); return; }
    
    // if the deleted node is head
    if ((*fds)->_fd == fd_to_close)
    {
        t_fd *new_head = (*fds)->_next;
        CLOSE_SUCCESS_DEBUG_LOG((*fds));
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
            if (iterator == *last_fd) *last_fd = previous;
            CLOSE_SUCCESS_DEBUG_LOG(iterator);
            close(iterator->_fd);
            free(iterator);
            return;
        }
        previous = iterator;
        iterator = iterator->_next;
    }

    // nothing was found
    CLOSE_FAIL_DEBUG_LOG();
}

void *register_fd_handler(t_fd **fds, t_fd **last_fd, va_list options)
{
    int new_fd = va_arg(options, int);
    open_pos open_origin = va_arg(options, open_pos);
    t_fd *original_fd = NULL;

    // allocation is already registered we dont register again
    if ((original_fd = fd_exists(fds, new_fd))) { REGISTER_FD_ALREADY_REGISTERED_LOG(); REGISTER_FAILED(); };

    t_fd *new_node = malloc(sizeof(t_alloc));
    if (!new_node) { REGISTER_FD_FAIL_DEBUG_LOG(); MALLOC_FAILED(); } // if failure we should FREE ALL and exit and close also all fds
    new_node->_fd = new_fd;
    new_node->_open_pos = open_origin;
    new_node->_next = NULL;

    REGISTER_FD_SUCCESS_DEBUG_LOG();
    if (!(*fds)) return *fds = new_node, *last_fd = new_node, OPEN_SERIALIZE new_fd; // if the list is empty add the malloc to the head;
    return (*last_fd)->_next = new_node, *last_fd = new_node, OPEN_SERIALIZE new_fd;
}