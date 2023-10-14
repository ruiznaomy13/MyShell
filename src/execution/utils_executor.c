
#include "inc/minishell.h"

void	count_process(t_all *all, char *str)
{
	int	i;
	int	n_proces;

	i = 0;
	n_proces = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			n_proces++;
		i++;
	}
	n_proces += 1;
	all->num_process = n_proces;
}

char	**duplicate_env(t_all *all)
{
	char	**new_env;
	int		i;

	i = 0;
	while (all->env[i++])
		;
	new_env = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (all->env[i])
	{
		new_env[i] = ft_strdup(all->env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

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