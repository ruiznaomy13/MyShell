/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:39:56 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/26 17:09:48 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"
# include "structs.h"
# include <limits.h>
# include <signal.h>
// # include <term.h>

/* ------------------------MAIN----------------------- */
void	ft_free_all(t_all *all, int error);

//senyals.c
int		init_signals(int mode);
void	do_sigign(int signum);
void	norm_handler(int sig, siginfo_t *data, void *non_used_data);
void	ninter_handler(int sig, siginfo_t *data, void *non_used_data);
void	heredoc_handler(int sig, siginfo_t *data, void *non_used_data);

//free_minishell.c
void	free_token_list(t_token *token);

/* -------------------- PARSER ------------------------- */
// create_process.c
void	rm_prev_tkns(t_all **all);
void	add_prcs(t_all *all, t_process *pcs);
void	create_process(t_all *all);
void	parser(t_all *all);

// create_redi.c
int		arg_size(t_token *tkn);
char	**save_arg(t_all *all);
void	add_rd(t_token *rd, t_process *pcs);
void	list_redirection(t_process *pcs, t_all *all);

// expansor.c
char	*search_env(char *str, t_env *env);
char	*expand_var(t_all *all, t_token *tkn, int prev);

// lexer.c
void	loop(t_all *all);
int		lexer(t_all *all);
int		minishell_structure(t_all *all);
int		create_token(t_all *all, char *str, int type);
void	add_token(t_token *tkn, t_all *all);
int		exec_parent(t_all *all);

// separators.c
int		delimiter(char c);
char	*is_text(char *str);
char	*is_text_first(char *str);

/* --------------------------- UTILS ---------------------*/
// utils
char	*ft_charjoin(char *s, char c);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*search_var(char *str);

// utils 2
int		ft_strcmp(const char *s1, const char *s2);
char	*split_env(char *str);
int		is_rd(int type);
int		ft_arr_len(void **ptr);
int		verify_rep_value(t_env *env, const char *str);

// built_utils.c
int		save_var_env(const char *src, t_all *all);
char	*rm_value(const char *str, char character);
void	delete_env_var(t_env **env, const char *str);
void	swap(t_env *a, t_env *b);
void	order_exp(t_env *env);

// built_utils2.c
void	actualize_env(t_all *all);
int		count_env_tokens(t_env *env);

/* ------------------------- CHECKER ---------------------*/
// checker.c
int		checker(t_all *all);
int		check_cometes(t_all *all, char *str);
int		syntax_checker(t_all *all);

// errors.c
int		ft_error(t_all *all, int error, char *msj);

/* ------------------------- BUILTINS ---------------------*/
//echo.c
int		ft_echo(char **argv);
int		n_flag(char *s);

//env.c
int		ft_env(t_all *all);
void	free_char_array(char ***arr);
void	add_to_env(t_all *all, t_env *env);
int		list_env(t_all *all, char **env);

//exit.c
int		ft_exit(t_process *pcs, t_all *all);
int		exit_prog(t_all *all, int output);

//export.c
void	show_sorted_exp(t_env *env);
int		save_var_env(const char *src, t_all *all);
int		ft_export(t_process *pcs, t_all *all);
int		ft_unset(t_process *pcs, t_all *all);

//pwd_cd.c
int		ft_pwd(void);
int		ft_cd(t_process *pcs, t_all *all);

/* ------------------------ EXECUTOR --------------------*/
//executor.c
void	executor(t_all *all);
void	child(t_all *all, t_process *prcs, int fd_pipe[2]);
void	aux_executor1(t_all *all, int fd_pipe[2], int fd_trm[2]);
void	aux_executor2(t_all *all, pid_t *pid, int fd_trm[2]);
void	wait_pipes(t_all *all, int num_process, pid_t *pid);

//executor2
int		exec_builting(t_all *all, t_process *pcs);
int		is_builting(char *cmd);
void	executor_builting(t_all *all, t_process *process);
int		list_env(t_all *all, char **env);

//pipes
void	dup_apunta_terminal(int fd_trm[2]);
void	init_pipes(int *pipe);
void	close_pipes(int *pipe);
void	father_redirect_stdin(int fd_pipe[2]);
void	dup2_apunta_terminal(int fd_trm[2]);

//finds
int		find_routes(t_all *all, t_process *prcs);
char	*find_path(t_all *all, int *found);
char	*get_ruta(t_all *all);//find cmd
char	*aux_get_ruta(t_all *all, char **path, char *ruta, char *tmp);

//redi
void	redi_type(t_all *all, t_process *prcs, int fd_pipe[2]);
void	open_infile(t_all *all, t_process *prcs, int fd_pipe[2]);
void	open_outfile(t_all *all, t_process *prcs, int fd_pipe[2]);
void	apendd(t_all *all, t_process *prcs, int fd_pipe[2]);
void	here_doc(t_process *prcs, int fd_pipe[2]);

//here_doc
void	check_heredoc(t_all *all, t_process *prcs);
void	create_heredoc(t_all *all, t_token *current_rd);
void	save_hd_fd(t_all *all, char *wrd, int fd[2]);
int		ft_close(int *fd);

//utils executor
void	count_process(t_all *all, char *str);
void	free_args_and_rd(t_all *all, t_process *aux_prcs);
void	free_rd_execve(t_all *all);
void	free_prcs_execve(t_all *all);

//utils executor2
void	add_var_env(t_all *all, t_env *env);
int		create_env_var(t_all *all, char *str);

#endif
