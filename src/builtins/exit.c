/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:28:07 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/28 14:54:07 by mmonpeat         ###   ########.fr       */
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
	clear_history();
	ft_free_all(all, E_EXIT);
	exit(all->error);
	return (output);
}

int	exit_type(t_all *all, t_process *pcs)
{
	if (ft_atoi(pcs->args[1]) == 127)
		return (exit_prog(all, CMD_NOT_FOUND));
	else if (ft_atoi(pcs->args[1]) == 1)
		return (exit_prog(all, E_EXIT));
	all->error = ft_atoi(pcs->args[1]);
	return (exit_prog(all, all->error));
}

int	ft_exit(t_process *pcs, t_all *all)
{
	ft_putstr_fd("exit\n", 2);
	if (!pcs->args[1])
		exit_prog(all, SUCCESS);
	else if (pcs->args[2])
		return (print_error("Too many arguments", 1));
	return (exit_type(all, pcs));
}
