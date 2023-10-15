/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:18:35 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/10/03 12:11:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	executor(t_all *all)
{
	int		i;//cal donar-li el valor de la quantitat d'arxius(redirecions) hi ha 
	int		exit_code;

	i = 0;//count_process nomes conta entre |, no redi, pt no posar arxius
	all->prcs->pos_process = 0;
	while (all->prcs && all->num_process > i)
	{
		if (all->prcs == NULL)
			return ;
		if (find_routes(all, all->prcs) == 1)
			exit(1);
		while (all->prcs->pos_process < all->num_process)// numero de prcs que s'han dexecutar
		{//crec que pos_process i i s'han de canviar, o posar num_proces
			if (i < all->num_process - 1 && pipe(all->prcs->fd))
				exit (1);
			all->prcs->pid_prc = fork();
            if (all->prcs->pid_prc == 0)
                child(all, all->prcs, all->prcs->pos_process);//crec que no cal pos_process
			last_pipe(all);
			all->prcs->pos_process++;
		}
		i++;
		printf("abans de prcs->next\n");
		all->prcs = all->prcs->next;
	}
	printf("abans de wait forks\n");
	if (all->prcs->pos_process == all->num_process)
	{
		exit_code = wait_forks(all);
		if (WIFEXITED(exit_code))
			exit(WEXITSTATUS(exit_code));
		exit(1);
	}
	printf("ERROR\n");
}

void child(t_all *all, t_process *prcs, int i)
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
	printf("\nall->prcs->pos_process: %i\n", i);
	all->prcs->ruta = get_ruta(all);
	//printf("ruta = %s\n", all->prcs->ruta);
    if (!all->prcs->ruta) {
    	exit(127);
	}
	execve(all->prcs->ruta, all->prcs->args, all->env);
	//perror("execve");
	exit(1);
}

char	*get_ruta(t_all *all)//find cmd
{
	char	**path;
	char	*ruta;
	char	*tmp;

	path = all->prcs->routes;
	if (!path)
		printf("ERROR, no existeix all->prcs->routes\n");
	//pipex.ruta = find_cmd(pipex.routes, pipex.args[0]);
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

