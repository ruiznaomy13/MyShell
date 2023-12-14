/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:37:32 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/14 19:19:56 by ncastell         ###   ########.fr       */
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
		printf("error al no fer split \n");
		return (1);
		//return (ft_error(1, ERR_MC, NULL));
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
	{
		printf("env no existeix \n");
		return (NULL);
	}
	while (all->env[i] && ft_strncmp(all->env[i], "PATH=", 5))
		i++;
	if (i > 30)
	{
		*found = 0;
		return (NULL);
	}
	*found = 1;
	// printf("routes: %s\n", all->env[i] + 5);
	return (all->env[i] + 5);
}
