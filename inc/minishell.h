/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:39:56 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/10/03 12:14:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../lib/readline/readline.h"
# include "../lib/readline/history.h"
# include "../lib/libft/libft.h"
# include "structs.h"


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
char	*ft_charjoin(char *s, char c);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char    *search_var(char *str);

// utils 2
char	*split_env(char *str);


// separadors
int		check_cometes(char *str);
int		delimiter(char c);
char	*is_text(char *str);
char	*is_text_first(char *str);
char	**duplicate_env(t_all *all);

// Expansiones
char	*search_env(char *str, char *env[]);
char	*expand_var(t_token *tkn, char **env);

// Expansiones
char	*search_env(char *str, char *env[]);
char	*expand_var(t_token *tkn, char **env);

// free de les llistes
void	ft_free(t_all *all);
void	ft_error(int error);

char	*str_rep(char* source, char* target, char* replacement);

// EXECUTOR
void 	executor(t_all *all);
void 	child(t_all *all, t_process *prcs, int i);
char	*get_ruta(t_all *all);//find cmd

//finds
int		find_routes(t_all *all, t_process *prcs);
char	*find_path(t_all *all, int *found);
void    close_pipes(t_process *prcs);
void	last_pipe(t_all *all);

//redi
void    redi_type(t_all *all, t_process *prcs);
void	open_infile(t_process *prcs);
void	open_outfile(t_process *prcs);
void	here_doc(t_process *prcs);
void	apendd(t_process *prcs);


//utils executor
char	**duplicate_env(t_all *all);
void	count_process(t_all *all, char *str);
int	    get_exit_code(t_all *all);

#endif
