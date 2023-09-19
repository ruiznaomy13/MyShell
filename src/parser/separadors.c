/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separadors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:04:54 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/19 19:23:57 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	delimiter(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == ' ')
		return (1);
	return (0);
}

char	*is_comma(char *str, char c)
{
	int		i;
	char	*new;

	i = 1;
	while (str[i] != c && str[i])
		i++;
	new = ft_substr(str, 1, i - 1);
	return (new);  //  recorremos el array hasta que acabe la ,
}

char	*is_text(char *str)
{
	int		i;
	char	*new;
	int		comma;

	i = 0;
	comma = 0;
	if (delimiter(str[i]))
		i++;
	while ((!delimiter(str[i]) && str[i]) && comma == 0)
		i++;
	new = ft_substr(str, 0, i);
	return (new);
}

char	*is_text_first(char *str)
{
	int		i;
	int		comma;

	i = 0;
	comma = 0;
	if (delimiter(str[i]))
		i++;
	while (str[i] && ((!delimiter(str[i]) && comma == 0) || comma != 0))
	{
		if ((!delimiter(str[i]) && comma == 0) && (str[i] != '\'' && str[i] != '\"'))
			i++;
		if ((str[i] == '\'' || str[i] == '\"') && comma == 0)
			comma = str[i];
		if (comma != 0)
		{
			i++;
			while (comma != str[i] && str[i])
				i++;
			comma = 0;
			i++;
		}
	}
	if (!comma)
        return NULL;
	return (ft_substr(str, 0, i));
}