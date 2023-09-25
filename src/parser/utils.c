/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:28:29 by ncastell          #+#    #+#             */
/*   Updated: 2023/09/25 18:06:47 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

/* Cambiar a funciones correctas IMPORTANTE*/
char	*ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t	src_len;
    size_t	i;
	
	i = 0;
	src_len = strnlen(src, n);
    if (dest == NULL || src == NULL || n == 0)
        return (dest);
	while (i < n)
	{
		if (i < src_len)
            dest[i] = src[i];
		i++;
	}
    dest[i] = '\0';
    return (dest);
}


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
char *search_env(char *str, char *env[])
{
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

/* CREAR FUNCIONES DE LIBFT <<<<<<<<<< IMPORTANT! >>>>>>>>>>>> */
char    *str_rep(char *source, char *target, char *replacement)
{
    size_t		i;
	char		*result;
	int			found;

    i = 0;
    result = NULL;
    found = 0;
    while (i < ft_strlen(source))
    {
        if (ft_strncmp(source + i, target, ft_strlen(target)) == 0 && !found) {
            result = (char*)malloc(ft_strlen(source) + ft_strlen(replacement) - ft_strlen(target) + 1);
            if (result == NULL)
                return (NULL);
            ft_strncpy(result, source, i);
            strcpy(result + i, replacement);
            strcpy(result + i + ft_strlen(replacement), source + i + ft_strlen(target));
            found = 1;
        }
        i++;
    }   
    if (!found)
        return strdup(source);
    return (result);
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
