
#ifndef ACCESS_MEM_H
#define ACCESS_MEM_H

#define NO_RETURN NULL
#define MALLOC_FAILED NULL
#define OPEN_FAILED NULL
#define NUKE_EXIT_CODE 77

#define BOLD_BLACK "\033[1;30m"       
#define BOLD_RED "\033[1;31m"         
#define BOLD_GREEN "\033[1;32m"       
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE "\033[1;34m"        
#define BOLD_PURPLE "\033[1;35m"      
#define BOLD_CYAN "\033[1;36m"        
#define BOLD_WHITE "\033[1;37m"      
#define END_COLOR "\033[0m"

#define WARNING_LOG BOLD_YELLOW "WARNING" END_COLOR
#define ERROR_LOG BOLD_RED "ERROR" END_COLOR
#define DEFAULT_LOG BOLD_GREEN "LOG" END_COLOR

#define OPEN_SERIALIZE (void *)(uintptr_t)
#define OPEN_DESERIALIZE (int)(uintptr_t)

#define ALLOC_CMD "alloc"

typedef struct s_alloc {
    void *_alloc;
    struct s_alloc *_next;
} t_alloc;

typedef struct s_fd {
    int _fd;
    struct s_fd *_next;
} t_fd;

typedef t_alloc * allocs_iterator;
typedef t_fd * fds_iterator;

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <fcntl.h>

// HANDLERS/OTHER_HANDLERS.C
void print_mem_handler(t_alloc *allocs);
void nuke_handler();

// HANDLERS/ALLOCS_HANDLERS.C
void *alloc_handler(t_alloc **allocs, size_t size);
void free_alloc_handler(t_alloc **allocs, void *alloc_to_free);
void free_all_handler(t_alloc **allocs);

// HANDLERS/FDS_HANDLERS.C
void *open_handler(t_fd **fds, va_list options);
void close_fd_handler(t_fd **fds, int fd_to_close);
void close_all_handler(t_fd **fds);

// UTILS.C
bool is_command(char *input, char *command);

// ACCESS_MEM.C
void *access_mem_ALLOC(size_t size);
int access_mem_OPEN(const char *pathname, int flags, ...);
void access_mem_PRINT_MEM();
void access_mem_FREE_ALL();
void access_mem_CLOSE_ALL();
void access_mem_FREE_ALLOC(void *alloc_to_free);
void access_mem_CLOSE_FD(int fd_to_close);
void access_mem_NUKE();


#endif