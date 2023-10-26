
#include "inc/minishell.h"

void	add_var_env(t_all *all, t_env *env)
{
	t_env	*aux;

	if (all->env == NULL)
		all->blt_env = env;
	else
	{
		aux = all->blt_env;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = env;
	}
}

int create_env_var(t_all *all, char *str)
{
	t_env	*env;
	char	**parts;
	int		i;

	i = -1;
	env = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (-1);
	env->key = NULL;
	env->value = NULL;
	parts = ft_split(str, '=');
	if (parts[0])
		env->key = ft_strdup(parts[0]);
	if (parts[1])
		env->value = ft_strdup(parts[1]);
	if(ft_strchr(str, '=') != NULL)
		env->equal = 1;
	while (parts[++i])
		free(parts[i]);
	free(parts);
	add_var_env(all, env);
	return (0);
}

int	built_env(t_all *all)
{
	int	i;

	i = -1;
	if (!all->env)
		return (-1);
	while (all->env[++i])
		create_env_var(all, all->env[i]);
	return (0);
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

