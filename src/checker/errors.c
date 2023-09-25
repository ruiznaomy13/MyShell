/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:59:20 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/25 19:56:22 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	ft_error(int error)
{
	if (error == '\'' || error == '\"')
		printf("syntax error near unexpected token %c\n", error);
}

int	count_procesos(char *str)
{
	int	i;
	int	n_proces;

	i = 0;
	n_proces = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			n_proces++;
		i++;
	}
	n_proces += 1;
	return (n_proces);
}
