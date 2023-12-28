/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:59:20 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/28 10:52:32 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	ft_error(t_all *all, int error, char *msj)
{
	if (error == SYNTAX_ERROR)
		ft_dprintf(RED"syntax error near unexpected token %s\n"WHITE, msj);
	else if (error == ACCESS_ERROR)
		ft_dprintf(RED"myShell🌞> cd: %s: %s\n"WHITE, all->prcs->args[1], msj);
	else if (error == CMD_NOT_FOUND)
		ft_dprintf(RED"myShell🌞> %s: command not found\n"WHITE, msj);
	else if (error == 2)
		ft_dprintf(RED"myShell🌞> %s: No such file or directory\n"WHITE, msj);
	else if (error == 130)
		ft_dprintf(RED"%s\n"WHITE, msj);
	else if (error == 131)
		ft_dprintf(RED"%s\n"WHITE, msj);
	all->error = error;
	return (error);
}
/*
	if (!all)
		printf("all == NULL\n");
	if (!error)
		printf("error == NULL\n");
	if (!msj)
		printf("msj == NULL\n");
*/