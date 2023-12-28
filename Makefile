NAME = minishell
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

INCS = -I./inc -I./ -I./lib/Libft -I$(HOME)/.brew/opt/readline/include
LIBFTA = -L./lib/libft -lft
READLINE = -L$(HOME)/.brew/opt/readline/lib -lreadline
SRCDIR = src/
OBJDIR = obj/

SRC_L = main/main.c main/signals.c main/free_minishell.c \
		parser/expansor.c parser/create_redi.c \
		parser/lexer.c parser/separadors.c parser/create_process.c \
		checker/errors.c checker/checker.c \
		builtins/echo.c builtins/env.c builtins/export.c builtins/exit.c builtins/pwd_cd.c \
		execution/executor.c execution/executor2.c \
		execution/finds.c execution/pipes.c execution/utils_executor.c execution/redi.c \
		execution/here_doc.c \
		utils/utils.c utils/utils2.c utils/built_utils.c utils/built_utils2.c

SRC = $(addprefix $(SRCDIR), $(SRC_L))
OBJECTS = $(addprefix $(OBJDIR), $(SRC:.c=.o))
DEPS 	= $(addprefix $(OBJDIR), $(addsuffix .d, $(basename ${SRC})))

all:
	@${MAKE} -C lib/libft/ --no-print-directory
	@${MAKE} $(NAME) --no-print-directory

$(OBJDIR)%.o: %.c Makefile
	@printf "Compiling objects\n"
	@mkdir -p $(@D)
	@gcc $(CFLAGS) $(INCS) -MMD -MP -c $< -o $@

$(NAME): $(OBJECTS) lib/libft/libft.a
	@mkdir -p $(@D)
	@gcc $(CFLAGS) -o $@ $(OBJECTS) $(LIBFTA) $(READLINE)
	@printf "\nCompiled successfully!\n"

-include	${DEPS}

fclean: clean
	@rm -rf $(NAME)
	@${MAKE} fclean -C lib/libft/ --no-print-directory
	@printf "\nAll cleaned!\n"

clean:
	@rm -rf $(OBJDIR) $(DEPSDIR)

re: fclean all

.PHONY: all clean fclean re
