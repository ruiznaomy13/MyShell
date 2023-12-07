/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:13:05 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/07 14:02:40 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	swap(t_env *a, t_env *b)
{
	char	*temp_key = a->key;
	char	*temp_value = a->value;
	int		temp_equal = a->equal;

	a->key = b->key;
	a->value = b->value;
	a->equal = b->equal;
	b->key = temp_key;
	b->value = temp_value;
	b->equal = temp_equal;
}

void	order_exp(t_env *env)
{
	int swapped;
	t_env *aux;
	t_env *saved;

	saved = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		aux = env;

		while (aux->next != saved)
		{
			if (ft_strcmp(aux->key, aux->next->key) > 0)
			{
				swap(aux, aux->next);
				swapped = 1;
			}
			aux = aux->next;
		}
		saved = aux;
	}
}

void	delete_env_var(t_env **env, const char *str)
{
	t_env	*prev;
	t_env	*current;
	char	*aux;

	prev = NULL;
	current = *env;
	aux = rm_value(str, '=');
	while (current != NULL)
	{
		if (!strcmp(current->key, aux))
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	save_var_env(const char *src, t_all *all)
{
	char	**dup_src;
	t_env	*aux_env;

	dup_src = ft_split(src, '=');
	if (!dup_src)
		return (-1);
	aux_env = ft_calloc(1, sizeof(t_env));
	if (!aux_env)
		return (free(dup_src), -1);
	aux_env->key = ft_strdup(dup_src[0]);
	if (ft_strchr(src, '='))
		aux_env->equal = 1;
	if(dup_src[1])
		aux_env->value = ft_strdup(dup_src[1]);
	else
		aux_env->value = NULL;
	add_to_env(all, aux_env);
	free_char_array(dup_src);
	return (0);
}

char	*rm_value(const char *str, char character)
{
	const char	*found;
	size_t		length;
	char		*newStr;
	
	found = ft_strchr(str, character);
	if (found == NULL)
		return strdup(str);
	length = found - str;
	newStr = ft_calloc(length + 1, sizeof(char));
	if (!newStr)
		return (NULL);
	ft_strncpy(newStr, str, length);
	newStr[length] = '\0';
	return (newStr);
}