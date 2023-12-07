/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:18:35 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/07 13:47:12 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

// void	ft_close(void)
// {
// 	int i = 3;
// 	while (i < OPEN_MAX)
// 		close(i++);
// }
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
	while (all->prcs && all->num_process > i++)
	{
		init_pipes(fd_pipe);
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
	dup2_apunta_terminal(fd_trm);
	wait_pipes(all->num_process, pid);
}

void	child(t_all *all, t_process *prcs, int fd_pipe[2])
{
	if (fd_pipe[0] != -1)
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], STDOUT_FILENO);
	}
	if (is_builting(prcs->args[0]))
		executor_builting(all, all->prcs);
	if (prcs->rd)
	{
		while (prcs->rd)
		{
			redi_type(all, all->prcs, fd_pipe);
			prcs->rd = prcs->rd->next;
		}
	}
	if (find_routes(all, all->prcs) == 1)
		exit(1);
	prcs->ruta = get_ruta(all);
	if (!prcs->ruta)
		exit(127);
	if (execve(prcs->ruta, prcs->args, all->env) == -1)
		exit(1);
	exit(0);
}

char	*get_ruta(t_all *all)
{
	char	**path;
	char	*ruta;
	char	*tmp;

	path = all->prcs->routes;
	if (!path)
		printf("ERROR, no existeix all->prcs->routes\n");
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		ruta = ft_strjoin(tmp, all->prcs->args[0]);
		if (!ruta)
		{
			printf("ERROR, NO TROBA LA RUTA DEL args[0] (executable)");
			//ft_error(1, ERR_MC, NULL);
			return (NULL);
		}
		free(tmp);
		if (access(ruta, F_OK | X_OK) == 0)
			return (ruta);
		free(ruta);
		path++;
	}
	if (access(all->prcs->args[0], F_OK | X_OK) == 0 && ft_strchr(all->prcs->args[0], '/'))
		return (all->prcs->args[0]);
	else
		printf("ERROR, NO TE ACCESS A all->prcs->args[0]");
	//ft_error(127, ERR_CNF, all->prcs->args[0]);
	
	return (NULL);
}
