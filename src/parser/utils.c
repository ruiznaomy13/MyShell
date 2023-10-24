/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:28:29 by ncastell          #+#    #+#             */
/*   Updated: 2023/10/21 20:50:18 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

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

char	*ft_charjoin(char *s, char c, int *iter)
{
	size_t	len;
	char	*str;
	int		i;

	i = -1;
	if (s != NULL)
		len = ft_strlen(s);
	else
		len = 0;
	str = (char *) malloc(sizeof(char) * (len + 2));
	if (!str)
		return (NULL);
	if (s != NULL)
	{
		while (s[++i])
			str[i] = s[i];
	}
	str[i] = c;
	str[++i] = '\0';
	if (iter != NULL)
		*iter += 1;
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


char	*search_var(char *str)
{
	int	i;

	i = 0;
	while (str[++i] && (ft_isalnum(str[i]) || str[i] == '_'))
		;
	return (ft_substr(str, 1, --i));
}