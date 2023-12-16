/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:18:35 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/16 16:42:09 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//quan es faci exit s'ha de fer close de trm 
void	executor(t_all *all)
{
	int		i;
	int		fd_pipe[2];
	int		fd_trm[2];
	pid_t	pid;

	i = 0;
	if (all->prcs == NULL)
		return ;
	dup_apunta_terminal(fd_trm);
	init_signals(N_INTERACT);
	while (all->prcs && all->num_process > i++)
	{
		init_pipes(fd_pipe);
		if (i != all->num_process && pipe(fd_pipe) == -1)
			exit(1);//ft_error();
		pid = fork();
		if (pid < 0)
			exit(1);//ft_error();
		else if (pid == 0)
			child(all, all->prcs, fd_pipe);
		if (i != all->num_process)
			father_redirect_stdin(fd_pipe);
		all->pos_process++;
		all->prcs = all->prcs->next;
	}
	aux_executor(all, pid, fd_trm);
}

void	aux_executor(t_all *all, pid_t pid, int fd_trm[2])
{
	dup2_apunta_terminal(fd_trm);
	wait_pipes(all, all->num_process, pid);
}

void	child(t_all *all, t_process *prcs, int fd_pipe[2])
{
	if (fd_pipe[0] != -1)
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], STDOUT_FILENO);
	}
	if (prcs->rd)
	{
		while (prcs->rd)
		{
			redi_type(all, all->prcs, fd_pipe);
			prcs->rd = prcs->rd->next;
		}
	}
	if (prcs->args && is_builting(prcs->args[0]))
		exec_builting(all, prcs);
	else if (!prcs->args && !is_builting(prcs->args[0]))
	{
		if (find_routes(all, all->prcs) == 1)
			exit (ft_error(all, 2, prcs->args[0]));
		prcs->ruta = get_ruta(all);
		if (!prcs->ruta)
		{
			exit (ft_error(all, 2, prcs->args[0]));
		}
		if (execve(prcs->ruta, prcs->args, all->env) == -1)
			exit (ft_error(all, CMD_NOT_FOUND, prcs->args[0]));
	}
	exit(0);
}

char	*get_ruta(t_all *all)
{
	char	**path;
	char	*ruta;
	char	*tmp;

	path = all->prcs->routes;
	if (!path)
		exit (ft_error(all, 2, all->prcs->args[0]));
	while (*path)
	{
		if (!path || !*path || !all->prcs->args || !*all->prcs->args)
			return (NULL);
		tmp = ft_strjoin(*path, "/");
		ruta = ft_strjoin(tmp, all->prcs->args[0]);
		if (!ruta)
			exit (ft_error(all, CMD_NOT_FOUND, "No such file or directory"));
		free(tmp);
		if (access(ruta, F_OK | X_OK) == 0)
			return (ruta);
		free(ruta);
		path++;
	}
	if (access(all->prcs->args[0], F_OK | X_OK) == 0 \
		&& ft_strchr(all->prcs->args[0], '/'))
		return (all->prcs->args[0]);
	else
		exit(ft_error(all, CMD_NOT_FOUND, all->prcs->args[0]));
	return (NULL);
}

void	wait_pipes(t_all *all, int num_process, pid_t pid)
{
	int		i;
	int		status;

	i = 0;
	while (num_process > i++)
	{
		if (pid == waitpid(-1, &status, 0))
		{
			if (WIFEXITED(status))
				ft_error(all, WEXITSTATUS(status), "Program exit");
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					ft_error(all, 130, "Interrupted");
				else if (WTERMSIG(status) == SIGQUIT)
					(1 && (ft_error(all, 131, "Quit")) \
						&& (ft_dprintf("Quit: 3\n")));
			}
			return ;
		}
	}
}
