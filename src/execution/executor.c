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

char	*get_ruta(t_all *all)
{
	char	**path;
	char	*join;
	char	*tmp;
	int		i;

	i = 0;
	path = ft_split(getenv("PATH"), ':');
	join = (char *)malloc(sizeof(char) * (2 + 1));//num de processos
	printf("hola\n");
	if (path == NULL)
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
void	executor(t_all *all)
{
	// int i;

	all->prcs->ruta = get_ruta(all);
	printf("ruta = %s\n", all->prcs->ruta);
	// for (i = 0; all->prcs->args[i]; i++)
	// 	printf("%s, ", all->prcs->args[i]);
	// printf("\n");
	execve(all->prcs->ruta, all->prcs->args, all->env);
	perror("execve");
}
//execve("/bin/ls", {ls, -la, src/}, env);
