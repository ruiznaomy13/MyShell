#include "inc/minishell.h"

//per després
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

char	*exp_var(char *str)
{
	char	*new;
	size_t	i;

	i = 0;
	new = getenv(str);
	if (new == NULL)
		return (NULL);
	while (str[i] != '=')
		i++;
	return (ft_substr(new, strlen(str) + 1, strlen(new) - i));
}
