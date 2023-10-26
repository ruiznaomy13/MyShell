#include "inc/minishell.h"


int	find_routes(t_all *all, t_process *prcs)
{
	int	found;

	prcs->routes = ft_split(find_path(all, &found), ':');
	if (!found)
		return (1);
	if (!prcs->routes)
		printf("error al no fer split \n");
		//return (ft_error(1, ERR_MC, NULL));
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
	if (!all->env[i])
	{
		*found = 0;
		return (NULL);
	}
	*found = 1;
	return (all->env[i] + 5);
}


void    close_pipes(t_process *prcs)
{
    close(prcs->fd[0]);
    close(prcs->fd[1]);
}