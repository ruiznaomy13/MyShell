/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:59:20 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/06 10:27:17 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	ft_error(int error, char *msj)
{
	if (error == '\'' || error == '\"')
		printf("syntax error near unexpected token %c\n", error);
	else if (error == SYNTAX_ERROR)
		printf("syntax error near unexpected token `newline' %s\n", msj);
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
