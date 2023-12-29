/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:59:20 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/29 20:06:04 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	ft_error(t_all *all, int error, char *msj)
{
	if (error == SYNTAX_ERROR)
		ft_dprintf("syntax error near unexpected token %s\n", msj);
	else if (error == ACCESS_ERROR)
	{
		if (all->prcs->args[1])
			ft_dprintf("myShell🌞> cd: %s: %s\n", all->prcs->args[1], msj);
		else
			ft_dprintf("myShell🌞> %s\n", msj);
	}
	else if (error == CMD_NOT_FOUND)
		ft_dprintf("myShell🌞> %s: command not found\n", msj);
	else if (error == 2)
		ft_dprintf("myShell🌞> %s: No such file or directory\n", msj);
	else if (error == 130)
		ft_dprintf("%s\n", msj);
	else if (error == 131)
		ft_dprintf("%s\n", msj);
	all->error = error;
	return (error);
}
