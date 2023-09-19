/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:39:56 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/19 16:08:14 by ncastell         ###   ########.fr       */
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

// char **construct_cmd_argv(s_token)
// {
//     // Hacer un malloc con el numero de tokens + 1
// }

// int echo(char **argv)
// {
//     int i;
//     i = 1;
//     while(argv[i]){
//         ft_printf("");
//         i++;
//     }
// }

// ls | export a="hola" | ls | ls | cat ls

typedef struct s_token
{
	int				type;
	char			*wrd;
	// int             len;
	struct s_token	*next;
	// struct s_token  *prev;
}	t_token;

typedef struct s_proces
{
	char			*proces;
	struct s_proces	*next;
	// t_token			*token;
}	t_proces;

typedef struct s_all
{
	char		*line;
	int			size;
	// char    **env;
	t_token		*token;
	t_proces	*procesos;
}	t_all;

//----------PARSER------------
//lexer creem tokens
void	lexer(t_all *all);
int		create_token(t_all *all, char *str, int type);
void	add_token(t_token *tkn, t_all *all);
// void	create_proces(t_all *all);

//separadors 
char	*is_comma(char *str, char c);
int		delimiter(char c);
char	*is_text_maria(char *str);

// MOSTRA EL NODE
void	mostra_tokens(t_all *all);
void	mostra_proces(t_all *all);

//free de les llistes
void	ft_free(t_all *all);

#endif