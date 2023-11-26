/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 12:18:28 by marvin            #+#    #+#             */
/*   Updated: 2023/11/25 14:17:30 by mmonpeat         ###   ########.fr       */
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

char *search_env2(char *str, t_env *env)
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

int	asign_var(t_all *all, char *str, char **aux, int i)
{
	char	*var;

	var = search_var(str);
	if (search_env2(var, all->w_env) != NULL)
		*aux = ft_strjoin(*aux, search_env2(var, all->w_env));
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
	int		i;
	int		flag;
	char	*str;
	char	*aux;

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
			aux = ft_charjoin2(aux, str[i]);
		i++;
	}
	//printf(" EXPAND VAR -> %s\n", aux);
	free(str);
	return (aux);
}
