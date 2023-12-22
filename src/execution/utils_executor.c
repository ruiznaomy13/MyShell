/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:37:54 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/21 20:16:48 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	count_process(t_all *all, char *str)
{
	t_token	*aux;

	(void)str;
	aux = all->token;
	all->num_process = 1;
	while (aux)
	{
		if (aux->type == PIPE)
			all->num_process++;
		aux = aux->next;
	}
}
