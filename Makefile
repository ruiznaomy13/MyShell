UTILS_DIR	= src/utils
M_SRCS		= src/main.c
 
# BUILT_SRCS  = src/built-ins/echo.c
# UTILS_SRCS  = $(UTILS_DIR)/utils_list_arg.c 
			
M_OBJS		= $(patsubst src/%.c, $(OBJECTS_DIR)/%.o, $(M_SRCS))
# BUILT_OBJS  = $(patsubst src/built-ins/%.c, $(OBJECTS_DIR)/%.o, $(BUILT_SRCS))
# UTILS_OBJS  = $(patsubst src/utils/%.c, $(OBJECTS_DIR)/%.o, $(UTILS_SRCS))
OBJECTS_DIR	= obj
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I inc/
LFLAGS		= -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
LRFLAG		= -lreadline
RM			= rm -f
NAME		= minishell
all:		$(NAME)
$(NAME): $(M_OBJS) $(BUILT_OBJS) $(UTILS_OBJS) $(GNL_OBJS) inc/minishell.h
	$(CC) -g $(CFLAGS) $(M_OBJS) $(BUILT_OBJS) $(UTILS_OBJS) -o $(NAME) $(LFLAGS) $(LRFLAG)
$(OBJECTS_DIR)/%.o : src/%.c inc/minishell.h | $(OBJECTS_DIR)
	$(CC) -c  $< -o $@ -I ~/.brew/opt/readline/include
# $(OBJECTS_DIR)/%.o : src/built-ins/%.c  src/built-ins/builtins.h | $(OBJECTS_DIR)
#     $(CC) -c  $< -o $@
# $(OBJECTS_DIR)/%.o : src/utils/%.c inc/minishell.h | $(OBJECTS_DIR)
#     $(CC) -c  $< -o $@
$(OBJECTS_DIR) :
	mkdir -p $(OBJECTS_DIR)
clean:
	$(RM) -r $(OBJECTS_DIR)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re