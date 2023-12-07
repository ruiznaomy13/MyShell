/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:59:20 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/07 14:09:03 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	ft_error(t_all *all, int error, char *msj)
{
	if (error == SYNTAX_ERROR)
		printf("syntax error near unexpected token %s\n", msj);
	all->error = error;
	return (error);
}

/*
int i = 0;
while (all->env[i] != NULL)
{
	printf("%s\n", all->env[i]);
	i++;
}
*/
