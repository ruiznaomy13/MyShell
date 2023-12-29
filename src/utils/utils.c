/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:28:29 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/29 15:15:45 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

#include <stddef.h>

size_t	ft_strnlen(const char *str, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && str[len] != '\0')
		len++;
	return (len);
}

char	*ft_charjoin(char *s, char c)
{
	size_t	len;
	char	*str;
	int		i;

	i = -1;
	len = 0;
	if (s != NULL)
		len = ft_strlen(s);
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
	free(s);
	return (str);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strnlen(src, n);
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
	if (str[1] == '?')
		return (ft_strdup("?"));
	else if (str[1] == '$')
		return (ft_strdup("$"));
	while (str[++i] && (ft_isalnum(str[i]) || str[i] == '_'))
		;
	return (ft_substr(str, 1, --i));
}
