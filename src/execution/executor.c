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

	i = 0;//count_process nomes conta entre |, no redi, pt no posar arxius
	while (all->prcs)
	{
		if (find_routes(all->prcs, all->env) == 1)
			exit(1);
		while (i < all->prcs->pos_process)// numero de prcs que s'han dexecutar
		{
			if (i < all->prcs->pos_process - 1 && pipe(all->prcs->fd))//
				exit (1);
			all->prcs->pid_prc = fork();
            if (all->prcs->pid_prc == 0)
                child(all, all->prcs, i);
			i++;
		}
		all->prcs = all->prcs->next;
	}
}

void child(t_all *all, t_process *prcs, int i)
{
	if (!prcs->rd)
	{
		dup2(prcs->fd[1], STDOUT_FILENO);
		close_pipes(prcs);
	}
	else
		printf("hi ha redirecions pt arxius\n");
	printf("i: %i\n", i);
	//all->prcs->ruta = get_ruta(all);
	pipex.ruta = find_cmd(pipex.routes, pipex.args[0]);
    if (!all->prcs->ruta)
        exit(127);
	//printf("ruta = %s\n", all->prcs->ruta);
	execve(all->prcs->ruta, all->prcs->args, all->env);
	perror("execve");
}

char	*get_ruta(t_all *all)//find cmd
{
	char	**path;
	char	*join;
	char	*tmp;
	int		i;

	path = all->prcs->routes;
	join = (char *)malloc(sizeof(char) * (2 + 1));//num de processos
	if (path == NULL)//mirar funcio errors per retornar l'error adecuat si path no existeix
	{
		fprintf(stderr, "Error al dividir PATH\n");//funcion prohibida. Usa write.
		exit(1);
	}
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		join = ft_strjoin(tmp, all->prcs->args[0]);
		printf("\n%s\n", join);
		if (access(join, F_OK) == 0 && access(join, X_OK) == 0)
			return (join);
		free(join);
		i++;
	}
	return (NULL);
}

