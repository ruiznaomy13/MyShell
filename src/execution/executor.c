/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:18:35 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/10/24 13:04:29 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	executor(t_all *all)
{
	int		i;

	i = 0;
	if (all->prcs == NULL)
			return ;//error
	while (all->prcs && all->num_process > i++)
	{
		if (find_routes(all, all->prcs) == 1)
			exit(1);
		if (i < all->num_process - 1 && pipe(all->prcs->fd))
			exit (1);
		all->prcs->pid_prc = fork();
		if (all->prcs->pid_prc < 0)
			printf("ERROR, el fork no funka 1");
        else if (all->prcs->pid_prc == 0)
			child(all, all->prcs);
		wait(NULL);
		all->pos_process++;
		all->prcs = all->prcs->next;
		all->pos_process = 0;
	}
}

void child(t_all *all, t_process *prcs)
{
	if (prcs->rd)
	{
		while (prcs->rd)
		{
			printf("hola redi\n");
			redi_type(all, all->prcs);
			prcs->rd = prcs->rd->next;
		}
	}
	else
	{
		dup2(prcs->fd[1], STDOUT_FILENO);
		close_pipes(prcs);
	}
	all->prcs->ruta = get_ruta(all);
    if (!all->prcs->ruta){
		printf("ERROR 127: No hay ruta");
		exit(127);
	}
	if (execve(all->prcs->ruta, all->prcs->args, all->env) == -1) {
		printf("EEEERROR\n");
		exit(1);
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

