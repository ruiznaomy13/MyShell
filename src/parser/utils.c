/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:28:29 by ncastell          #+#    #+#             */
/*   Updated: 2023/09/28 15:56:49 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char *ft_charjoin(char *s, char c)
{
	size_t	len;
	char	*str;
	int		i;

	i = -1;
	len = (s != NULL) ? strlen(s) : 0;
	str = (char *) malloc(sizeof(char) * (len + 2));
	if (!str)
		return (NULL);
	if (s != NULL)
	{
		while (s[++i])
			str[i] = s[i];
	}
	str[i] = c;
	str[i+1] = '\0';
	return (str);
}

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

char    *search_var(char *str)
{
	int i;

	i = 0;
	while (str[++i] && (ft_isalnum(str[i]) || str[i] == '_'));
	printf("SEARCH VAR = %s\n", ft_substr(str, 1, i));
	return(ft_substr(str, 1, i-1));
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
