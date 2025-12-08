
#ifndef CONST_MACROS_H
# define CONST_MACROS_H

// DEBUG MODE
# ifdef AM_DEBUG_LOGS
#  define DEBUG 0x1 // 1 for TRUE
# else
#  define DEBUG 0x0 // 0 for FALSE
# endif

# ifndef DEVELOPMENT
// COLORS
#  define BOLD_BLACK "\033[1;30m"       
#  define BOLD_RED "\033[1;31m"         
#  define BOLD_GREEN "\033[1;32m"       
#  define BOLD_YELLOW "\033[1;33m"
#  define BOLD_BLUE "\033[1;34m"        
#  define BOLD_PURPLE "\033[1;35m"      
#  define BOLD_CYAN "\033[1;36m"        
#  define BOLD_WHITE "\033[1;37m"      
#  define END_COLOR "\033[0m"

// LOGS
#  define WARNING_LOG COLOR("WARNING", BOLD_YELLOW)
#  define MALLOC_LOG COLOR("MALLOC", BOLD_BLUE)
#  define REGISTER_LOG COLOR("REGISTER", BOLD_BLUE)
#  define FREE_LOG COLOR("FREE", BOLD_PURPLE)
#  define ERROR_LOG COLOR("ERROR", BOLD_RED)
#  define DEFAULT_LOG COLOR("LOG", BOLD_GREEN)
#  define OPEN_LOG COLOR("OPEN", BOLD_BLUE)
#  define CLOSE_LOG COLOR("CLOSE", BOLD_PURPLE)

// SERIALIZATION
#  define OPEN_SERIALIZE (void *)(uintptr_t)
#  define OPEN_DESERIALIZE (int)(uintptr_t)

// UTILS
#  define NO_RETURN NULL
#  define OPEN_FAILED NULL
#  define NUKE_DEFAULT_EXIT_CODE 0x0
# endif

// PUBLIC MACROS FOR FUNCTIONS USAGE
# define _AM_EXIT_ON _AM_TRUE
# define _AM_EXIT_OFF _AM_FALSE

# define _AM_TRUE 0x1
# define _AM_FALSE 0x0

#endif