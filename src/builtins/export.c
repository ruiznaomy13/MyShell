/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:44:17 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/27 17:36:31 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	show_exp(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux != NULL)
	{
		printf("declare -x %s", aux->key);
		if (aux->equal)
			printf("=");
		// printf("llego aqui\n");
		if (aux->value)
			printf("%s", aux->value);
		printf("\n");
		aux = aux->next;
	}
	return (0);
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

int	check_var(t_env *w_env, char *str)
{
	char	*aux;

	aux = rm_value(str, '=');
	printf("STR == %s\n", aux);
	if (verify_rep_value(w_env, aux))
	{
		printf("Hay una variable repetida\n");
		return (1);
	}
	free(aux);
	return (0);
}

int delete_rep(t_env **env, const char *str)
{
    t_env *prev = NULL;
    t_env *current = *env;
	char	*aux;

	aux = rm_value(str, '=');
    while (current != NULL) {
        if (!strcmp(current->key, aux)) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                *env = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    
    return 0;
}

int	ft_export(t_process *pcs, t_all *all)
{
	int	i;

	i = 0;
	if (!pcs->args[1]) // if there is just 1 arg
		show_exp(all->w_env); // just show it
	else
	{
		while(pcs->args[++i])
		{
			delete_rep(&all->w_env, pcs->args[i]); // we delete rep vars
			save_var_env(pcs->args[1], all); // and save the new arg
		}
	}
	return (0);
}