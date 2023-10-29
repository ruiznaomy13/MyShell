/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:39:56 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/10/24 12:55:27 by ncastell         ###   ########.fr       */
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


//------------------------MAIN-----------------------
void	ft_free(t_all *all);
// MOSTRA EL NODE ----- DELETE
void	mostra_tokens(t_all *all);
void	mostra_process(t_all *all);
void	mostra_rd(t_process *pcs);

//-----------------------PARSER--------------------------------

// create_process.c
void    rm_prev_tkns(t_all *all);
void    add_prcs(t_all *all, t_process *pcs);
void    create_process(t_all *all);
void	parser(t_all *all);

// create_redi.c
int	    arg_size(t_token *tkn);
char    **save_arg(t_all *all);
void	add_rd(t_token *rd, t_process *pcs);
void    list_redirection(t_process *pcs, t_all *all);
// expansor.c
char	*search_env(char *str, char *env[]);
char	*expand_var(t_token *tkn, char **env);

// lexer.c
void	loop(t_all *all);
int		lexer(t_all *all);
int		create_token(t_all *all, char *str, int type);
void	add_token(t_token *tkn, t_all *all);

// separators.c
int	    delimiter(char c);
char	*is_text(char *str);
char	*is_text_first(char *str);

// utils
char    *str_rep(char *source, char *target, char *replacement);
// char	*ft_charjoin(char *s, char c);
char	*ft_charjoin(char *s, char c, int *iter);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char    *search_var(char *str);

// utils 2
char	*split_env(char *str);
int 	is_rd(int type);
int     ft_arr_len(void **ptr);

/* --------------------------- CHECKER ---------------------*/
// checker.c
int		checker(t_all *all);
int		check_cometes(char *str);
int		syntax_checker(t_all *all);

// errors.c
void	ft_error(int error);

/* --------------------------- BUILTINS ---------------------*/
int 	ft_echo(char **argv);
int 	ft_env(char **env);
int     ft_exit(t_all *all);

/* --------------------------- EXECUTOR ---------------------*/
//executor.c
void    executor(t_all *all);
void    child(t_all *all, t_process *prcs, int input_pipe[2], int output_pipe[2]);
char	*get_ruta(t_all *all);//find cmd

//executor2
int     ft_strcmp(const char *s1, const char *s2);
int     exec_builting(t_process *pcs, char **env);
int     is_builting(char *cmd);
void	executor_builting(t_all *all);

//pipes
void	init_pipes(int *pipe);
void    close_pipes(int *pipe);
void    wait_pipes(int num_process);
void    check_pipes(int input_pipe[2], int output_pipe[2]);

//finds
int		find_routes(t_all *all, t_process *prcs);
char	*find_path(t_all *all, int *found);

//redi
void    redi_type(t_all *all, t_process *prcs);
void	open_infile(t_process *prcs);
void	open_outfile(t_process *prcs);
void	here_doc(t_process *prcs);
void	apendd(t_process *prcs);


//utils executor
char	**duplicate_env(t_all *all);
void	count_process(t_all *all, char *str);
void    routes_pipe(t_all *all, int i, int output_pipe[2]);


//utils executor2
void	add_var_env(t_all *all, t_env *env);
int     create_env_var(t_all *all, char *str);
int		built_env(t_all *all);

#endif
