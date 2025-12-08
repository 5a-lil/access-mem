
#include "includes.h"

static void *access_mem(char *COMMAND, ...)
{
    static t_alloc *allocs = NULL;
    static t_alloc *last_alloc = NULL;
    static t_fd *fds = NULL;
    static t_fd *last_fd = NULL;

    va_list options;
    va_start(options, COMMAND);
    if (is_command(COMMAND, "alloc"))
        return alloc_handler(&allocs, &last_alloc, options);
    else if (is_command(COMMAND, "open"))
        return open_handler(&fds, &last_fd, options);
    else if (is_command(COMMAND, "log_allocs"))
        log_allocs_handler(allocs);
    else if (is_command(COMMAND, "log_fds"))
        log_fds_handler(fds);
    else if (is_command(COMMAND, "free"))
        free_alloc_handler(&allocs, &last_alloc, options);
    else if (is_command(COMMAND, "close"))
        close_handler(&fds, &last_fd, options);
    else if (is_command(COMMAND, "register_alloc"))
        return register_alloc_handler(&allocs, &last_alloc, options);
    else if (is_command(COMMAND, "register_fd"))
        return register_fd_handler(&fds, &last_fd, options);
    else if (is_command(COMMAND, "nuke"))
        nuke_handler(&allocs, &fds, options);
    va_end(options);
    return NO_RETURN;
}

void access_mem_LOG_ALLOCS() { access_mem("log_allocs"); }

void access_mem_LOG_FDS() { access_mem("log_fds"); }

void *access_mem_ALLOC(size_t size, alloc_pos alloc_origin) { return access_mem("alloc", size, alloc_origin); }

void *access_mem_REGISTER_ALLOC(void *new_alloc, alloc_pos alloc_origin) { return access_mem("register_alloc", new_alloc, alloc_origin); }

void *access_mem_REGISTER_FD(int new_fd, open_pos open_origin) { return access_mem("register_fd", new_fd, open_origin); }

void access_mem_FREE_ALLOC(void *alloc_to_free, ...) 
{ 
    if (DEBUG)
    {
        va_list debug;
        va_start(debug, alloc_to_free);
        log_stats debugger = va_arg(debug, log_stats);
        va_end(debug);
        access_mem("free", alloc_to_free, debugger); 
    }
    else
        access_mem("free", alloc_to_free); 
}

int access_mem_OPEN(const char *pathname, int flags, open_pos open_origin, ...) 
{
    if (flags & O_CREAT)
    {
        va_list options;
        va_start(options, open_origin);
        mode_t mode = va_arg(options, mode_t);
        va_end(options);
        return OPEN_DESERIALIZE access_mem("open", pathname, flags, open_origin,  mode); 
    }
    return OPEN_DESERIALIZE access_mem("open", pathname, flags, open_origin); 
}

void access_mem_CLOSE(int fd_to_close, ...) 
{
    if (DEBUG) 
    {
        va_list debug;
        va_start(debug, fd_to_close);
        log_stats debugger = va_arg(debug, log_stats);
        va_end(debug);
        access_mem("close", fd_to_close, debugger); 
    }
    else
        access_mem("close", fd_to_close); 
}

void access_mem_NUKE(_am_bool exit_or_not, /*exit code arg if used*/...) 
{ 
    if (exit_or_not == _AM_EXIT_ON)
    {
        va_list options;
        va_start(options, exit_or_not);
        int exit_code = va_arg(options, int);
        va_end(options);
        access_mem("nuke", _AM_EXIT_ON, exit_code);     
    }
    else
        access_mem("nuke", _AM_EXIT_OFF); 
}