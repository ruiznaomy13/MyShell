/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:28:07 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/29 17:46:44 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	print_error(const char *msj, int otput)
{
	if (otput == -1)
		ft_dprintf("myShell 🌞: exit: %s: numeric argument required\n", msj);
	else
		ft_dprintf("%s\n", msj);
	return (otput);
}

long long int	ft_exit_atoi(const char *str)
{
	int						i;
	int						sign;
	unsigned long long int	res;

	i = 0;
	res = 0;
	sign = 1;
	if ((str[i] < 48 || str[i] > 57) && (str[i] != 43 && str[i] != 45))
		return (print_error(str, -1));
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if ((res > LLONG_MAX && sign == 1) || (res - 1 > LLONG_MAX && sign == -1))
		return (print_error(str, -1));
	return (sign * res);
}

int	exit_prog(t_all *all, int output)
{
	ft_dprintf(YELLOW"BYE :D\n"WHITE);
	clear_history();
	ft_free_all(all, E_EXIT);
	if (output)
		exit(output);
	exit (all->error);
	return (output);
}

int	exit_type(t_all *all, t_process *pcs)
{
	int	error_num;

	error_num = ft_exit_atoi(pcs->args[1]);
	if (error_num == -1)
		exit_prog(all, 255);
	if (error_num == CMD_NOT_FOUND)
		return (exit_prog(all, CMD_NOT_FOUND));
	else if (error_num == E_EXIT)
		return (exit_prog(all, E_EXIT));
	all->error = error_num;
	return (exit_prog(all, all->error));
}

int	ft_exit(t_process *pcs, t_all *all)
{
	if (!pcs->args[1])
		exit_prog(all, SUCCESS);
	else if (pcs->args[2])
		return (print_error("Too many arguments", 1));
	return (exit_type(all, pcs));
}
