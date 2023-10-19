/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:59:20 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/09/28 13:58:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	ft_error(int error)
{
	if (error == '\'' || error == '\"')
		printf("syntax error near unexpected token %c\n", error);
	else if (error == 5)
		printf("syntax error near unexpected token `newline'\n");
}

/*
int i = 0;
while (all->env[i] != NULL)
{
	printf("%s\n", all->env[i]);
	i++;
}
*/
