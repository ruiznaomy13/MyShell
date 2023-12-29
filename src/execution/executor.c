/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:21:08 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/29 18:14:12 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_all *all)
{
	int			i;
	pid_t		pid;
	int			fd_pipe[2];
	int			fd_trm[2];
	t_process	*aux_prcs;

	i = 0;
	aux_prcs = all->prcs;
	aux_executor1(all, fd_pipe, fd_trm);
	while (all->prcs && all->num_process >= i++)
	{
		if (i != all->num_process && pipe(fd_pipe) == -1)
			exit(1);
		pid = fork();
		if (pid < 0)
			exit(1);
		else if (pid == 0)
			child(all, all->prcs, fd_pipe);
		if (i != all->num_process)
			father_redirect_stdin(fd_pipe);
		all->pos_process++;
		all->prcs = all->prcs->next;
	}
	aux_executor2(all, &pid, fd_trm);
	free_args_and_rd(all, aux_prcs);
}

void	aux_executor1(t_all *all, int fd_pipe[2], int fd_trm[2])
{
	if (all->prcs == NULL)
		return ;
	dup_apunta_terminal(fd_trm);
	init_signals(N_INTERACT);
	init_pipes(fd_pipe);
}

void	aux_executor2(t_all *all, pid_t *pid, int fd_trm[2])
{
	dup2_apunta_terminal(fd_trm);
	wait_pipes(all, all->num_process, pid);
	if (g_sig)
		all->error = g_sig;
}

void	child(t_all *all, t_process *prcs, int fd_pipe[2])
{
	close(fd_pipe[0]);
	dup2(fd_pipe[1], STDOUT_FILENO);
	if (prcs->rd)
	{
		while (prcs->rd)
		{
			redi_type(all, prcs, fd_pipe);
			prcs->rd = prcs->rd->next;
		}
	}
	if (prcs->args && is_builting(prcs->args[0]))
		exec_builting(all, prcs);
	else if (!g_sig && prcs->args && *prcs->args)
	{
		if (find_routes(all, all->prcs) == 1)
			exit (ft_error(all, 2, prcs->args[0]));
		prcs->ruta = get_ruta(all);
		if (!prcs->ruta)
			exit (ft_error(all, 2, prcs->args[0]));
		if (execve(prcs->ruta, prcs->args, all->env) == -1)
			exit (ft_error(all, CMD_NOT_FOUND, prcs->args[0]));
	}
	exit(0);
}

void	wait_pipes(t_all *all, int num_process, pid_t *pid)
{
	int		i;
	int		status;

	i = 0;
	while (i < num_process)
	{
		if (*pid == waitpid(-1, &status, 0))
		{
			if (WIFEXITED(status))
				all->error = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					ft_error(all, 130, "");
				else if (WTERMSIG(status) == SIGQUIT)
					(1 && (ft_error(all, 131, "Quit: 3")));
			}
		}
		i++;
	}
}
