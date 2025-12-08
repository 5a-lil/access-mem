
#ifndef STRUCTS_H
# define STRUCTS_H

// UTILS
typedef struct s_pos {
    int _line;
    const char *_func_name;
    const char *_var_name;
} t_pos;

typedef t_pos log_stats;
typedef t_pos alloc_pos;
typedef t_pos open_pos;

// ALLOCATION STRUCT
typedef struct s_alloc {
    void *_alloc; // the address of the allocation
    alloc_pos _alloc_pos; // the t_pos struct to know where the allocation comes from
    struct s_alloc *_next; // _next node for linked list property
} t_alloc;

typedef t_alloc * allocs_iterator;

// FD STRUCT
typedef struct s_fd {
    int _fd; // the fd
    open_pos _open_pos; // the t_pos struct to know where the open comes from
    struct s_fd *_next; // _next node for linked list property
} t_fd;

typedef t_fd * fds_iterator;

// OTHERS
typedef int _am_va_arg_bool;
typedef int _am_bool;

#endif