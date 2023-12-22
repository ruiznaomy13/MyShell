/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:37:32 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/22 13:24:51 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	find_routes(t_all *all, t_process *prcs)
{
	int		found;
	char	*path_find;

	found = 0;
	path_find = find_path(all, &found);
	if (!path_find)
		return (1);
	prcs->routes = ft_split(path_find, ':');
	if (!prcs->routes)
	{
		ft_error(all, 2, prcs->args[0]);
		return (1);
	}
	if (!found)
		return (1);
	return (0);
}

char	*find_path(t_all *all, int *found)
{
	int	i;

	i = 0;
	if (!all->env)
		return (NULL);
	while (all->env[i] && ft_strncmp(all->env[i], "PATH=", 5))
		i++;
	if (i > 30)
	{
		*found = 0;
		return (NULL);
	}
	*found = 1;
	return (all->env[i] + 5);
}

char	*get_ruta(t_all *all)
{
	char	**path;
	char	*ruta;
	char	*tmp;

	ruta = NULL;
	tmp = NULL;
	path = all->prcs->routes;
	if (!path)
		exit (ft_error(all, 2, all->prcs->args[0]));
	while (*path)
	{
		ruta = aux_get_ruta(all, path, ruta, tmp);
		if (ruta)
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

char	*aux_get_ruta(t_all *all, char **path, char *ruta, char *tmp)
{
	if (!path || !*path || !all->prcs->args || !*all->prcs->args)
		return (NULL);
	tmp = ft_strjoin(*path, "/");
	ruta = ft_strjoin(tmp, all->prcs->args[0]);
	if (!ruta)
		exit (ft_error(all, CMD_NOT_FOUND, "No such file or directory"));
	free(tmp);
	if (access(ruta, F_OK | X_OK) == -1)
		return (NULL);
	return (ruta);
}
