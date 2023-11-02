
#include "inc/minishell.h"

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

void    routes_and_pipe(t_all *all, int i, int output_pipe[2])
{
	if (find_routes(all, all->prcs) == 1)
		exit(1);//fer funcio d'error que printeji l'error i faci exit(1);
	printf("\n\n\ni: %i < num_prcs: %i\n", i, all->num_process);
	if (i < all->num_process)
	{
		if (pipe(output_pipe) == -1)
			exit(1);//fer funcio d'error que printeji l'error i faci exit(1);
	}
	else
		init_pipes(output_pipe);
}