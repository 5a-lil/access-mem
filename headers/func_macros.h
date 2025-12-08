
#ifndef LOGS_H
# define LOGS_H

# ifndef DEVELOPMENT
// LOGS MACROS
/// OPEN
#   define OPEN_FAIL_DEBUG_LOG() \
      if (DEBUG) printf("[%s]: Opening file at path [\"%s\"] failed\n", ERROR_LOG, pathname)
#   define OPEN_SUCCESS_DEBUG_LOG() \
      if (DEBUG) printf("[%s]: New open of file [%s] has been successfully done at line [%d] in function [%s]\n", OPEN_LOG, pathname, open_origin._line, open_origin._func_name);

/// CLOSE
#   define CLOSE_FAIL_DEBUG_LOG() \
      if (DEBUG) printf("[%s]: File descriptor [%d] isn't registered/doesn't exists\n", WARNING_LOG, fd_to_close);
#   define CLOSE_SUCCESS_DEBUG_LOG(iterator) \
      if (DEBUG) { log_stats debugger = va_arg(options, log_stats); printf("[%s]: FD [%d] in variable [%s] was closed at line [%d] in function [%s] and originally opened at line [%d] in function [%s]\n", CLOSE_LOG, fd_to_close, debugger._var_name, debugger._line, debugger._func_name, iterator->_open_pos._line, iterator->_open_pos._func_name); };
#   define CLOSE_ALL_DEBUG_LOG() \
      if (DEBUG) { printf( COLOR("->", BOLD_WHITE) " Closed fd: [" BOLD_WHITE "%d" END_COLOR "]\nOpen origin: line [" COLOR("%d", BOLD_WHITE) "] in function [" COLOR("%s", BOLD_WHITE) "]\n\n", (*fds)->_fd, (*fds)->_open_pos._line, (*fds)->_open_pos._func_name); };

/// REGISTER_FD
#   define REGISTER_FD_FAIL_DEBUG_LOG() \
      if (DEBUG) printf("[%s]: Failed to register [%s] fd in memory at line [%d] in function [%s]\n", ERROR_LOG, open_origin._var_name, open_origin._line, open_origin._func_name);
#   define REGISTER_FD_SUCCESS_DEBUG_LOG() \
      if (DEBUG) printf("[%s]: New fd [%s] has been successfully registered at line [%d] in function [%s]\n", REGISTER_LOG, open_origin._var_name, open_origin._line, open_origin._func_name);
#   define REGISTER_FD_ALREADY_REGISTERED_LOG() \
      if (DEBUG) printf("[%s]: fd from [%s] is already registered in memory at line [%d] in function [%s]\n", WARNING_LOG, open_origin._var_name, original_fd->_open_pos._line, original_fd->_open_pos._func_name);

/// MALLOC
#   define MALLOC_FAIL_DEBUG_LOG() \
      if (DEBUG) printf("[%s]: Malloc of size [%zu] failed at line [%d] in function [%s]\n", ERROR_LOG, size, alloc_origin._line, alloc_origin._func_name);
#   define MALLOC_SUCCESS_DEBUG_LOG() \
      if (DEBUG) printf("[%s]: New malloc of size [%zu] has been successfully allocated at line [%d] in function [%s]\n", MALLOC_LOG, size, alloc_origin._line, alloc_origin._func_name);

/// REGISTER_ALLOC
#   define REGISTER_ALLOC_FAIL_DEBUG_LOG() \
      if (DEBUG) printf("[%s]: Failed to register [%s] alloc in memory at line [%d] in function [%s]\n", ERROR_LOG, alloc_origin._var_name, alloc_origin._line, alloc_origin._func_name);
#   define REGISTER_ALLOC_SUCCESS_DEBUG_LOG() \
      if (DEBUG) printf("[%s]: New allocation [%s] has been successfully registered at line [%d] in function [%s]\n", REGISTER_LOG, alloc_origin._var_name, alloc_origin._line, alloc_origin._func_name);
#   define REGISTER_ALLOC_ALREADY_REGISTERED_LOG() \
      if (DEBUG) printf("[%s]: Address [%s] is already registered in memory at line [%d] in function [%s]\n", WARNING_LOG, alloc_origin._var_name, original_alloc->_alloc_pos._line, original_alloc->_alloc_pos._func_name);

// / FREE
#   define FREE_FAIL_DEBUG_LOG() \
      if (DEBUG) { log_stats debugger = va_arg(options, log_stats); printf("[%s]: Address [%p] in variable [%s] isn't registered/dynamically allocated at line [%d] in function [%s]\n", WARNING_LOG, alloc_to_free, debugger._var_name, debugger._line, debugger._func_name); };
#   define FREE_SUCCESS_DEBUG_LOG(iterator) \
      if (DEBUG) { log_stats debugger = va_arg(options, log_stats); printf("[%s]: Address [%p] in variable [%s] was freed at line [%d] in function [%s] and originally allocated at line [%d] in function [%s]\n", FREE_LOG, alloc_to_free, debugger._var_name, debugger._line, debugger._func_name, iterator->_alloc_pos._line, iterator->_alloc_pos._func_name); };
#   define FREE_ALL_DEBUG_LOG() \
      if (DEBUG) { printf( COLOR("->", BOLD_WHITE) " Freed address: [" BOLD_WHITE "%p" END_COLOR "]\nAllocation origin: line [" COLOR("%d", BOLD_WHITE) "] in function [" COLOR("%s", BOLD_WHITE) "]\n\n", (*allocs)->_alloc, (*allocs)->_alloc_pos._line, (*allocs)->_alloc_pos._func_name); };

// / MEM_LOG
#   define MEM_LOG() \
      printf(COLOR("->", BOLD_WHITE) " Allocation address: [" BOLD_WHITE "%p" END_COLOR "]\nAllocation origin: line [" COLOR("%d", BOLD_WHITE) "] in function [" COLOR("%s", BOLD_WHITE) "]\n\n", iterator->_alloc, iterator->_alloc_pos._line, iterator->_alloc_pos._func_name)

// / NUKE
#   define NUKE_START_DEBUG_LOG() \
      if (DEBUG) printf("[%s]: Nuking environment... 💥\n", DEFAULT_LOG)
#   define NUKE_SUCCESS_DEBUG_LOG() \
      if (DEBUG) printf("[%s]: Your environment was nuked succefully ✅\n", DEFAULT_LOG)

// UTILS MACROS
#   define COLOR(text, color) \
      color text END_COLOR
#   define MALLOC_FAILED() \
      return _AM_NUKE_EXIT(NUKE_DEFAULT_EXIT_CODE), NULL
#   define REGISTER_FAILED() \
      return NULL
# endif

// HANDLERS MACROS
# define _AM_FREE(alloc_to_free) \
      DEBUG ? access_mem_FREE_ALLOC(alloc_to_free, (log_stats){__LINE__, __func__, #alloc_to_free}) \
      : access_mem_FREE_ALLOC(alloc_to_free)

# define _AM_CLOSE(fd_to_close) \
      DEBUG ? access_mem_CLOSE(fd_to_close, (log_stats){__LINE__, __func__, #fd_to_close}) \
      : access_mem_CLOSE(fd_to_close)

# define _AM_MALLOC(size) \
      access_mem_ALLOC(size, (alloc_pos){__LINE__, __func__, NULL})

# define _AM_OPEN(pathname, flags, ...) \
      (flags) & O_CREAT ? access_mem_OPEN(pathname, flags, (open_pos){__LINE__, __func__, NULL}, ##__VA_ARGS__) \
      : access_mem_OPEN(pathname, flags, (open_pos){__LINE__, __func__, NULL})

# define _AM_REGISTER_ALLOC(new_alloc) \
      access_mem_REGISTER_ALLOC(new_alloc, (alloc_pos){__LINE__, __func__, #new_alloc})

# define _AM_REGISTER_FD(new_fd) \
      access_mem_REGISTER_FD(new_fd, (open_pos){__LINE__, __func__, #new_fd})

# define _AM_LOG_MEM() \
      access_mem_LOG_MEM()

# define _AM_NUKE_EXIT(opt_exit_code) \
      access_mem_NUKE(_AM_EXIT_ON, opt_exit_code)
# define _AM_NUKE_NO_EXIT() \
      access_mem_NUKE(_AM_EXIT_OFF)

#endif