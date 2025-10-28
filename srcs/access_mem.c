
#include "access_mem.h"

static void *access_mem(char *COMMAND, ...)
{
    static t_alloc *allocs = NULL;
    static t_fd *fds = NULL;

    va_list options;
    va_start(options, COMMAND);
    if (is_command(COMMAND, "alloc"))
        return alloc_handler(&allocs, va_arg(options, size_t));
    else if (is_command(COMMAND, "open"))
        return open_handler(&fds, options);
    else if (is_command(COMMAND, "print_mem"))
        print_mem_handler(allocs);
    else if (is_command(COMMAND, "free_all"))
        free_all_handler(&allocs);
    else if (is_command(COMMAND, "close_all"))
        close_all_handler(&fds);
    else if (is_command(COMMAND, "free_alloc"))
        free_alloc_handler(&allocs, va_arg(options, void *));
    else if (is_command(COMMAND, "close_fd"))
        close_fd_handler(&fds, va_arg(options, int));
    else if (is_command(COMMAND, "nuke"))
        nuke_handler();
    return NO_RETURN;
    va_end(options);
}

void access_mem_PRINT_MEM() { access_mem("print_mem"); }

void *access_mem_ALLOC(size_t size) { return access_mem("alloc", size); }

int access_mem_OPEN(const char *pathname, int flags, ...) 
{
    if (flags & O_CREAT)
    {
        va_list options;
        va_start(options, flags);
        mode_t mode = va_arg(options, mode_t);
        va_end(options);
        return OPEN_DESERIALIZE access_mem("open", pathname, flags, mode); 
    }
    return OPEN_DESERIALIZE access_mem("open", pathname, flags); 
}

void access_mem_FREE_ALL() { access_mem("free_all"); }

void access_mem_CLOSE_ALL() { access_mem("close_all"); }

void access_mem_FREE_ALLOC(void *alloc_to_free) { access_mem("free_alloc", alloc_to_free); }

void access_mem_CLOSE_FD(int fd_to_close) { access_mem("close_fd", fd_to_close); }

void access_mem_NUKE() { access_mem("nuke"); }