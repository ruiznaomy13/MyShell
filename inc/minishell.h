/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:39:56 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/10/18 22:16:04 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

# define TEXT 00
# define PIPE 01
# define COMMA_S 21
# define COMMA_D 22
# define RDOUT 31
# define RDAP 32
# define RDIN 41
# define RDHD 42
# define EXP 05

typedef struct s_token
{
	int				type;
	char			*wrd;
	int				fd[2];
	struct s_token	*next;
}	t_token;

typedef struct s_process
{
	int					pos_process;
	char				**args; //lo que ejecutaremos
	t_token				*rd; // la lista de tokens de la ejecució
	char				*ruta;
	struct s_process	*next;
}	t_process;

typedef struct s_all
{
	char		*line;
	int			size;
	char		**env;
	t_token		*token;
	t_process	*prcs;
	int			num_process;
}	t_all;

// MOSTRA EL NODE ----- DELETE
void	mostra_tokens(t_all *all);
void	mostra_process(t_all *all);
void	mostra_rd(t_process *pcs);

//----------PARSER------------
// lexer 
void	loop(t_all *all);
void	lexer(t_all *all);
int		create_token(t_all *all, char *str, int type);
void	add_token(t_token *tkn, t_all *all);
void	create_process(t_all *all);

/* ------- CHECKER -------*/
int		checker(t_all *all);
int		check_cometes(char *str);
void	parser(t_all *all);
int		syntax_checker(t_all *all);
 
// utils
char	**duplicate_env(char **env);
char	*ft_charjoin(char *s, char c);
char	*split_env(char *str);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char    *search_var(char *str);

// utils 2
void	count_process(t_all *all, char *str);
int		is_rd(int type);
int 	ft_arr_len(void **ptr);

// separadors
int		delimiter(char c);
char	*is_text(char *str);
char	*is_text_first(char *str);

// Expansiones
char	*search_env(char *str, char *env[]);
char	*expand_var(t_token *tkn, char **env);

// free de les llistes
void	ft_free(t_all *all);
void	ft_error(int error);

char	*str_rep(char* source, char* target, char* replacement);

// EXECUTOR
void	executor(t_all *all);
void	executor_builting(t_all *all);

// BUILTINS
int 	ft_echo(char **argv);
int 	ft_env(char **env);
#endif
