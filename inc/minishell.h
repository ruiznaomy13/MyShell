/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:39:56 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/07 14:03:42 by mmonpeat         ###   ########.fr       */
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
# include <limits.h>

//------------------------MAIN-----------------------
void	ft_free(t_all *all);
// MOSTRA EL NODE ----- DELETE
void	mostra_tokens(t_all *all);
void	mostra_process(t_all *all);
void	mostra_rd(t_process *pcs);

//-----------------------PARSER--------------------------------

// create_process.c
void	rm_prev_tkns(t_all *all);
void	add_prcs(t_all *all, t_process *pcs);
void	create_process(t_all *all);
void	parser(t_all *all);
int     check_heredoc(t_all *all);

// create_redi.c
int		arg_size(t_token *tkn);
char	**save_arg(t_all *all);
void	add_rd(t_token *rd, t_process *pcs);
void	list_redirection(t_process *pcs, t_all *all);

// expansor.c
char	*search_env(char *str, char *env[]);
char	*search_env2(char *str, t_env *env);
char	*expand_var(t_all *all, t_token *tkn);

// lexer.c
void	loop(t_all *all);
int		lexer(t_all *all);
int		create_token(t_all *all, char *str, int type);
void	add_token(t_token *tkn, t_all *all);

// separators.c
int		delimiter(char c);
char	*is_text(char *str);
char	*is_text_first(char *str);

/* --------------------------- UTILS ---------------------*/
// utils
char	*str_rep(char *source, char *target, char *replacement);
char	*ft_charjoin(char *s, char c, int *iter);
char	*ft_charjoin2(char *s, char c);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*search_var(char *str);

// utils 2
char	*split_env(char *str);
int		is_rd(int type);
int		ft_arr_len(void **ptr);

// built_utils.c
int		save_var_env(const char *src, t_all *all);
char	*rm_value(const char *str, char character);
void	delete_env_var(t_env **env, const char *str);
void	swap(t_env *a, t_env *b);
void	order_exp(t_env *env);

/* --------------------------- CHECKER ---------------------*/
// checker.c
int		checker(t_all *all);
int		check_cometes(char *str);
int		syntax_checker(t_all *all);

// errors.c
void	ft_error(int error);

/* --------------------------- BUILTINS ---------------------*/
//echo.c
int		ft_echo(char **argv);
int		n_flag(char *s);

//env.c
int		ft_env(t_all *all);
void	free_char_array(char **arr);
void	add_to_env(t_all *all, t_env *env);
int		list_env(t_all *all, char **env);

//exit.c
int		ft_exit(t_process *pcs, t_all *all);

//export.c
void	show_sorted_exp(t_env *env);
int		save_var_env(const char *src, t_all *all);
int		ft_export(t_process *pcs, t_all *all);
int		ft_unset(t_process *pcs, t_all *all);

//pwd_cd.c
int		ft_pwd();
int		ft_cd(t_process *pcs, t_all *all);

/* --------------------------- EXECUTOR ---------------------*/
//executor.c
void	executor(t_all *all);
void	child(t_all *all, t_process *prcs, int fd_pipe[2]);
char	*get_ruta(t_all *all);//find cmd

//executor2
int		ft_strcmp(const char *s1, const char *s2);
int		exec_builting(t_all *all, t_process *pcs, t_env *env);
int		is_builting(char *cmd);
void	executor_builting(t_all *all, t_process *process);
int		list_env(t_all *all, char **env);

//pipes
void	dup_apunta_terminal(int fd_trm[2]);
void	init_pipes(int *pipe);
void	close_pipes(int *pipe);
void	father_redirect_stdin(int fd_pipe[2]);
void	dup2_apunta_terminal(int fd_trm[2]);
void	wait_pipes(int num_process, pid_t pid);

//finds
int		find_routes(t_all *all, t_process *prcs);
char	*find_path(t_all *all, int *found);

//redi
void	redi_type(t_all *all, t_process *prcs, int fd_pipe[2]);
void	open_infile(t_process *prcs, int fd_pipe[2]);
void	open_outfile(t_process *prcs, int fd_pipe[2]);
void	apendd(t_process *prcs, int fd_pipe[2]);
void	here_doc(t_process *prcs, int fd_pipe[2]);

//here_doc
void	save_hd_fd(t_process *prcs, int i);

//utils executor
char	**duplicate_env(char **env);
void	count_process(t_all *all, char *str);

//utils executor2
void	add_var_env(t_all *all, t_env *env);
int		create_env_var(t_all *all, char *str);
int		built_env(t_all *all);

#endif
