/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:28:29 by ncastell          #+#    #+#             */
/*   Updated: 2023/09/24 22:33:07 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"


char *split_env(char *str)
{
	int		j;
    char	**sep;
	char	*value;
	
	sep = ft_split(str, '=');
    if (sep != NULL)
	{
        value = ft_strdup(sep[1]);
        j = -1;
        while (sep[++j] != NULL)
            free(sep[j]);
        free(sep);
        return (value);
    }
    return (NULL);
}

// str = string a buscar en el env
char *search_env(char *str, char *env[]) {
    int i;
    char *new;
    char *aux;

	i = -1;
    new = ft_strdup(str);
    aux = NULL;
    if (new == NULL)
        return NULL;
    ft_strlcat(new, "=", ft_strlen(new));
    while (env[++i])
	{
        aux = ft_strnstr(env[i], new, ft_strlen(new));
        if (aux != NULL)
		{
            free(new);
            return (split_env(aux));
        }
    }
    free(new); // Liberamos la memoria asignada a new si no se encuentra
    return (NULL);
}

