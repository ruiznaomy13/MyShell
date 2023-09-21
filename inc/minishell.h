/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:39:56 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/21 17:16:14 by ncastell         ###   ########.fr       */
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
	// int             len;
	struct s_token	*next;
	// struct s_token  *prev;
}	t_token;

typedef struct s_process
{
	char				**process; //lo que ejecutaremos
	t_token				*rd; // la lista de tokens de la ejecució
	struct s_process	*next;
	// t_token			*token;
}	t_process;

typedef struct s_all
{
	char		*line;
	int			size;
	char    	**env;
	t_token		*token;
	t_process	*procesos;
}	t_all;

//----------PARSER------------
// lexer 
void	loop(t_all *all);
void	checker(t_all *all);
void	lexer(t_all *all);
int		create_token(t_all *all, char *str, int type);
void	add_token(t_token *tkn, t_all *all);
void    create_process(t_all *all);
 
// utils
char	*search_env(char *str, char *env[]);

// separadors 
int		check_cometes(char *str);
int		delimiter(char c);
char	*is_text(char *str);
char	*is_text_first(char *str);

// MOSTRA EL NODE ----- DELETE
void	mostra_tokens(t_all *all);
void	mostra_proces(t_all *all);

// free de les llistes
void	ft_free(t_all *all);
void	ft_error(int error);

#endif