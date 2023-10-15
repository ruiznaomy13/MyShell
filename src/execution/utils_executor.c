
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

int	wait_forks(t_all *all)
{
	int	status;
	int	exit_code;

	while (all->prcs->pos_process > 0)//all->prcs->pos_process > 2 + pipex->here_doc i que si hi ha redirecions
	{
		if (wait(&status) == all->prcs->pid_prc)
			exit_code = status;
		all->prcs->pos_process--;
	}
	return (exit_code);
}
