
#ifndef DECLARATIONS_H
# define DECLARATIONS_H

# include "types.h"

# ifndef DEVELOPMENT
// ../SRCS/HANDLERS/OTHER_HANDLERS.C
void log_allocs_handler(t_alloc *allocs);
void log_fds_handler(t_fd *fds);
void nuke_handler(t_alloc **allocs, t_fd **fds, va_list options);

// ../SRCS/HANDLERS/ALLOCS_HANDLERS.C
void *alloc_handler(t_alloc **allocs, t_alloc **last_alloc, va_list options);
void free_alloc_handler(t_alloc **allocs, t_alloc **last_alloc, va_list options);
void *register_alloc_handler(t_alloc **allocs, t_alloc **last_alloc, va_list options);

// ../SRCS/HANDLERS/FDS_HANDLERS.C
void *open_handler(t_fd **fds, t_fd **last_fd, va_list options);
void close_handler(t_fd **fds, t_fd **last_fd, va_list options);
void *register_fd_handler(t_fd **fds, t_fd **last_fd, va_list options);

// ../SRCS/UTILS.C
_am_bool is_command(char *input, char *command);
t_alloc *alloc_exists(t_alloc **allocs, void *alloc);
t_fd *fd_exists(t_fd **fds, int fd);
# endif

// ../SRCS/ACCESS_MEM.C
void *access_mem_ALLOC(size_t size, alloc_pos alloc_origin);
int access_mem_OPEN(const char *pathname, int flags, open_pos open_origin, /*open declaration variadic args*/...);
void access_mem_LOG_ALLOCS();
void access_mem_LOG_FDS();
void access_mem_FREE_ALLOC(void *alloc_to_free, /*needed for debug mode*/...);
void access_mem_CLOSE(int fd_to_close, ...);
void access_mem_NUKE(_am_bool exit_or_not, /*exit code arg if used*/...); 
void *access_mem_REGISTER_ALLOC(void *new_alloc, alloc_pos alloc_origin);
void *access_mem_REGISTER_FD(int new_fd, open_pos open_origin);

#endif