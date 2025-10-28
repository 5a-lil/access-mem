
#include "access_mem.h"

bool is_command(char *input, char *command) { return strcmp(input, command) == 0 ? true : false; }