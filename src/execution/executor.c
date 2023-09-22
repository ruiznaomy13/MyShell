/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:18:35 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/22 17:28:45 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	executor(t_all *all)
{
	char	**path;
	char	**join = NULL;
	int		i;

	i = 0;
	path = ft_split(getenv("PATH"), ':');
	if (path == NULL)
	{
		fprintf(stderr, "Error al dividir PATH\n");
		exit(1);
	}
	while (path[i])
	{
		printf("\n%s", path[i]);
		*join = ft_strjoin(path[i], "ls");
		if (access(join[0], F_OK) == 0)
		{
			execve(join[0],  "ls -la", all->env);
			perror("execve"); // Manejo de errores si execve falla
		}
		i++;
	}
	// exit(1);
}
//execve("/bin/ls", {ls, -la, src/}, env);
