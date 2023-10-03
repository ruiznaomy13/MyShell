NAME = minishell
CFLAGS = -Wall -Wextra -Werror -MMD #-fsanitize=address
FILES = main/main.c \
		parser/lexer.c parser/separadors.c parser/create_process.c parser/utils.c \
		parser/utils2.c parser/expansor.c \
		checker/errors.c \
		builthings/echo.c \
		execution/executor.c

SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(FILES))
CC = cc

OBJ_DIR = objects/
OBJS = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))
DEPS = $(addprefix $(OBJ_DIR), $(FILES:.c=.d))
RM = rm -rf
LIB = lib/libft/libft.a lib/readline/libreadline.a lib/readline/libhistory.a


$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -DREADLINE_LIBRARY=1 -I./ -Ilib/libft -Ilib/readline -c $< -o $@

all:
	@$(MAKE) -C lib/libft
	@$(MAKE) -C lib/readline &> /dev/null;
	@$(MAKE) $(NAME)

$(NAME):: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -Llib/libft -lft -Llib/readline/library -lreadline -lhistory -o $@

$(NAME)::
	@echo -n

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) clean -C lib/libft  
	@$(MAKE) clean -C lib/readline &> /dev/null

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(DEPS)