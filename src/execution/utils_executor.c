
#include "../inc/minishell.h"

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

int	find_routes(t_process *prcs, char **env)
{
	int	found;

	prcs->routes = ft_split(find_path(env, &found), ':');
	if (!found)
		return (1);
	if (!prcs->routes)
		printf("error al no fer split \n");
		//return (ft_error(1, ERR_MC, NULL));
	return (0);
}

char	*find_path(char **env, int *found)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!env[i])
	{
		*found = 0;
		return (NULL);
	}
	*found = 1;
	return (env[i] + 5);
}

void    close_pipes(t_process *prcs)
{
    colse(prcs.fd[0]);
    colse(prcs.fd[1]);
}