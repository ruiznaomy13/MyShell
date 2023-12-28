/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:28:07 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/28 21:45:54 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

long long int	ft_exit_atoi(const char *str)
{
	int	i;
	int	sign;
	unsigned long long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
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
	};
	if ((res > LLONG_MAX && sign == 1) || (res - 1 > LLONG_MAX && sign == -1))
	{
		printf("2 -> %llu, %d\n", res, MAX_EXIT_CODE);
		return (-1);
	}
	return (sign * res);
}

int	print_error(const char *msj, int otput)
{
	ft_dprintf("%s\n", msj);
	return (otput);
}

int	exit_prog(t_all *all, int output)
{
	ft_dprintf(YELLOW"BYE :D\n"WHITE);
	clear_history();
	ft_free_all(all, E_EXIT);
	// printf("output: %d\nerror: %d\n", output, all->error);
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
