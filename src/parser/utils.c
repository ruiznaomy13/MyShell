/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:28:29 by ncastell          #+#    #+#             */
/*   Updated: 2023/09/22 19:28:41 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*save;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = strlen(s);
	if (len > len_s - start)
		len = len_s - start;
	if (start >= len_s)
	{
		save = (char *)malloc(1);
		if (!save)
			return (NULL);
		save[0] = '\0';
		return (save);
	}
	save = (char *)malloc(sizeof(char) * (len + 1));
	if (!save)
		return (NULL);
	while (start--)
		s++;
	strlcpy(save, s, len + 1);
	return (save);
}

char    *search_env(char *str, char *env[])
{
	int i = 0;
	char *new;
	char *aux;

	new = strdup(str);
	aux = NULL;
	if (new == NULL)
		return NULL;
	strcat(new, "=");
	while (env[i] != NULL)
	{
		aux = strnstr(env[i], new, strlen(new));
		if (aux != NULL)
		{
			free(new); // Liberamos la memoria asignada a new
			return (aux);
		}
		i++;
	}
	free(new); // Liberamos la memoria asignada a new si no se encuentra
	return (NULL);
}

char *exp_var(char *str, char *env[])
{
	char    *new;
	size_t     i;
	i = 0;
	new = search_env(str, env);
	if (new == NULL)
		return NULL;
	while (str[i] != '=')
		i++;
	return (ft_substr(new, strlen(str) + 1, strlen(new) - i));
}

// int main(int ac, char **av, char *env[])
// {
// 	if (ac != 2)
// 		return (-1);
// 	printf("%s -> %s\n", search_env(av[1], env), exp_var(av[1], env));
// }