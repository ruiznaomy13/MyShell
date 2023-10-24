/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 12:18:28 by marvin            #+#    #+#             */
/*   Updated: 2023/10/21 21:01:13 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

// str = string a buscar en el env
char *search_env(char *str, char *env[])
{
	int		i;
	char	*new;
	char	*aux;

	i = -1;
	new = ft_strdup(str);
	aux = NULL;
	if (new == NULL)
		return NULL;
	new = ft_charjoin(new, '=', NULL);
	while (env[++i])
	{
		aux = ft_strnstr(env[i], new, ft_strlen(new));
		if (aux != NULL)
		{
			free(new);
			return (split_env(aux));
		}
	}
	free(new);
	return (NULL);
}

int	set_exp_flag(char c, int *flag)
{
	if ((c == '\'' || c == '\"') && *flag == 0)
	{
		if (c == '\'')
			*flag = COMMA_S;
		else
			*flag = COMMA_D;
		return (1);
	}
	else if ((c == '\"' && *flag == COMMA_D) || (c == '\'' && *flag == COMMA_S))
	{
		*flag = 0;
		return (1);
	}
	return (0);
}

char    *expand_var(t_token *tkn, char **env)
{
	int i = 0;
	int flag = 0;
	char *str;
	char *aux;
	char *var = NULL;

	aux = "";
	str = ft_strdup(tkn->wrd);
	//(0 || (i = 0) || (flag = 0) || (var = NULL));
	while (str[i])
	{
		set_exp_flag(str[i], &flag);
		if (str[i] == '$' && (flag == 0 || flag == COMMA_D))
		{
			var = search_var(&str[i]);
			if (search_env(var, env) != NULL)
				aux = ft_strjoin(aux, search_env(var, env));
			i += ft_strlen(var) + 1;
		}
		else
			aux = ft_charjoin(aux, str[i], &i);
	}
	free(str);
	return (aux);
}
