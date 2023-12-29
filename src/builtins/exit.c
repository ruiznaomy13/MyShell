/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:28:07 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/29 20:10:18 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	print_error(const char *msg, int type, int otput)
{
	if (type == 1)
		ft_dprintf("myShell 🌞: exit: %s: numeric argument required\n", msg);
	else if (type == 2)
		ft_dprintf("myShell 🌞: export: `%s': not a valid identifier\n", msg);
	else
		ft_dprintf("myShell 🌞: %s\n", msg);
	return (otput);
}

int	ft_exit_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	b;
	unsigned long long	n;

	i = 0;
	n = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] < 48 || str[i] > 57)
		return (print_error(str, 1, -1));
	while (str[i] >= '0' && str[i] <= '9')
	{
		b = str[i] - '0';
		if (n > ULONG_MAX / 10 || (n == ULONG_MAX / 10 && b > ULONG_MAX % 10))
			return (print_error(str, 1, -1));
		n = n * 10 + b;
		i++;
	}
	return (sign * n);
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
	else if (pcs->args[2] && ft_exit_atoi(pcs->args[1]) != -1)
		return (print_error("Too many arguments", 0, 1));
	return (exit_type(all, pcs));
}
