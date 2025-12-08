
COMPILE = cc
INCLUDES_DIR = headers
COMPILE_FLAGS = -Wall -Werror -Wextra -I./headers/ -DAM_DEBUG_LOGS

ARCHIVE = ar -rcs 

#### srcs ####
HANDLERS_DIR = handlers
HANDLERS_SRCS = $(addprefix $(HANDLERS_DIR)/, allocs_handlers.c fds_handlers.c other_handlers.c)
LIB_SRCS_DIR = srcs
LIB_SRCS = access_mem.c \
		   $(HANDLERS_SRCS) \
		   utils.c
LIB_OBJS_DIR = objs
LIB_OBJS = $(LIB_SRCS:%.c=$(LIB_OBJS_DIR)/%.o)
##############

LIB_NAME = access_mem.a

# TEST_FILE = main
# MAIN = $(LIB_SRCS_DIR)/main.c

##### test rule with main #####
# test: lib # regle just pour creer un test executable pour le main
# 	$(COMPILE) $(COMPILE_FLAGS) $(MAIN) $(LIB_NAME) -o $(TEST_FILE)
###############################

lib: COMPILE_FLAGS := $(filter-out -D%, $(COMPILE_FLAGS)) 
lib: $(LIB_NAME) # rule to create lib without DEBUG MODE

debug: $(LIB_NAME) # rule to create lib in DEBUG MODE

$(LIB_NAME): $(LIB_OBJS_DIR) $(LIB_OBJS)
	$(ARCHIVE) $(LIB_NAME) $(LIB_OBJS) 

$(LIB_OBJS_DIR)/%.o: $(LIB_SRCS_DIR)/%.c
	$(COMPILE) $(COMPILE_FLAGS) -c $< -o $@

$(LIB_OBJS_DIR):
	@mkdir -p $(LIB_OBJS_DIR) $(LIB_OBJS_DIR)/$(HANDLERS_DIR)

clean:
	@rm -rf $(LIB_OBJS_DIR)

fclean: clean
	@rm -rf $(LIB_NAME)
# 	@rm -rf $(TEST_FILE)

re-lib: fclean lib
re-debug: fclean debug

# re: fclean test
