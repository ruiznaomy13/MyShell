/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:28:07 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/07 18:38:09 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	print_error(char *msj, int otput)
{
	printf("%s\n", msj);
	return (otput);
}

int	exit_prog(t_all *all, int output)
{
	(void)all;
	exit(output);
	return (output);
}

int	exit_type(t_all *all, t_process *pcs)
{
	if (ft_atoi(pcs->args[1]) == 127)
		return (exit_prog(all, CMD_NOT_FOUND));
	else if (ft_atoi(pcs->args[1]) == 1)
		return (exit_prog(all, E_EXIT));
	return (0);
}

int	ft_exit(t_process *pcs, t_all *all)
{
	ft_putstr_fd("exit\n", 2);
	if (!pcs->args[1])
		exit_prog(all, SUCCESS);
	else if (pcs->args[1])
		return (exit_type(all, pcs));
	else
		return(print_error("Too many arguments", 1));
	return (0);
}
