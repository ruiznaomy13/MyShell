/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 12:18:28 by marvin            #+#    #+#             */
/*   Updated: 2023/09/30 12:18:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

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
    new = ft_charjoin(new, '=');
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

char    *expand_var(t_token *tkn, char **env)
{
	int i;
	int flag;
	char *str;
	char *aux;
	char *var;

	i = 0;
	flag = 0;
	aux = "";
	var = NULL;
	str = ft_strdup(tkn->wrd);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && flag == 0)
		{
			if (str[i] == '\'')
				flag = COMMA_S;
			else
				flag = COMMA_D;
			i++;
		}
		else if ((str[i] == '\"' && flag == COMMA_D) || (str[i] == '\'' && flag == COMMA_S))
		{
			flag = 0;
			i++;
		}
		else if (str[i] == '$' && (flag == 0 || flag == COMMA_D))
		{
			var = search_var(&str[i]);
			if (search_env(var, env) != NULL)
				aux = ft_strjoin(aux, search_env(var, env));
			i += ft_strlen(var) + 1;
		}
		else {
			aux = ft_charjoin(aux, str[i]);
			i++;
		}
	}
	free(str);
	return (aux);
}
