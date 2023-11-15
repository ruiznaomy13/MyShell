NAME = minishell
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

INCS = -I./ -I./lib/Libft -I$(HOME)/.brew/opt/readline/include
LIBFTA = -L./lib/libft -lft
READLINE = -L$(HOME)/.brew/opt/readline/lib -lreadline
SRCDIR = src/
OBJDIR = obj/

SRC_L = main/main.c \
		parser/expansor.c \
		parser/lexer.c parser/separadors.c parser/create_process.c \
		parser/utils.c parser/utils2.c \
		checker/errors.c checker/checker.c\
		builtins/echo.c builtins/env.c \
		execution/executor.c execution/executor2.c

SRC = $(addprefix $(SRCDIR), $(SRC_L))
OBJECTS = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(OBJDIR)%.o: %.c
	@printf "Compiling objects\n"
	@mkdir -p $(@D)
	@gcc $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJECTS) Makefile
	@mkdir -p $(@D)
	@gcc $(CFLAGS) -o $@ $(OBJECTS) $(LIBFTA) $(READLINE)
	@printf "\nCompiled successfully!\n"

fclean: clean
	@rm -rf $(NAME)

clean:
	@rm -rf $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
