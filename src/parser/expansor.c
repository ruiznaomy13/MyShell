/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:00:46 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/21 17:51:13 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char *search_env(char *str, t_env *env)
{
	int 	i;
	char 	*str_aux;
	char 	*aux;
	t_env	*node_iter;

	i = -1;
	node_iter = env;
	str_aux = ft_strdup(str);
	aux = NULL;
	if (str_aux == NULL)
		return NULL;
	while (node_iter)
	{
		if (!ft_strcmp(node_iter->key, str_aux))
		{
			free(str_aux);
			return (node_iter->value);
		}
		node_iter = node_iter->next;
	}
	free(str_aux);
	return (NULL);
}

int	asign_var(t_all *all, char *str, char **aux, int i)
{
	char	*var;

	var = search_var(str);
	if (search_env(var, all->w_env) != NULL)
		*aux = ft_strjoin(*aux, search_env(var, all->w_env));
	else
		*aux = ft_strjoin(*aux, "");
	i += ft_strlen(var);
	return (i);
}

int	save_comma(char c)
{
	if (c == '\'')
		return (COMMA_S);
	return (COMMA_D);
}

char	*expand_var(t_all *all, t_token *tkn)
{
	int i;
	int flag;
	char *str;
	char *aux;

	aux = "";
	str = ft_strdup(tkn->wrd);
	((0) || (i = 0) || (flag = 0));
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && flag == 0)
			flag = save_comma(str[i]);
		else if ((str[i] == '\"' && flag == COMMA_D) \
		|| (str[i] == '\'' && flag == COMMA_S))
			flag = 0;
		else if (str[i] == '$' && (flag == 0 || flag == COMMA_D))
			i = asign_var(all, &str[i], &aux, i);
		else
			aux = ft_charjoin(aux, str[i]);
		i++;
	}
	printf(" EXPAND VAR -> %s\n", aux);
	free(str);
	return (aux);
}
