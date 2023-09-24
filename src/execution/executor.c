/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:18:35 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/24 16:44:01 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	executor(t_all *all)
{
	char	**path;
	char	**join = NULL;
	int		i;
	int		j;

	i = 0;
	j = 0;
	path = ft_split(getenv("PATH"), ':');
	join = (char **)malloc(sizeof(char *) * (2 + 1));//num de processos
	if (path == NULL)
	{
		fprintf(stderr, "Error al dividir PATH\n");//ns com funca
		exit(1);
	}
	while (path[i])
	{
		// printf("\n%s", path[i]);
		*join = ft_strjoin(path[i], "/");
		*join = ft_strjoin(*join, all->procesos->process[i]);
		// exit (1);
		printf("\n%s", join[0]);
		if (access(join[0], F_OK) == 0 && access(join[0], X_OK) == 0)
		{
			printf("\nentra\n");
			execve(join[0], &all->procesos->process[i], all->env);
			perror("execve"); // Manejo de errores si execve falla
		}
		i++;
	}
		// all->procesos->next;
	printf("\n");
	while (j < 2) 
	{
		free(join[j]);
		j++;
	}
	free(join);

	// exit(1);
}
//execve("/bin/ls", {ls, -la, src/}, env);
