/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:18:35 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/30 16:44:03 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	exec_parent(t_all *all)
{
	if (all->num_process != 1 || !all->prcs->args || !*all->prcs->args)
		return (0);
	if (!ft_strcmp(all->prcs->args[0], "export") && !all->prcs->args[1])
		return (0);
	if (!ft_strcmp(all->prcs->args[0], "export") \
	|| !ft_strcmp(all->prcs->args[0], "unset") \
	|| !ft_strcmp(all->prcs->args[0], "cd") \
	|| !ft_strcmp(all->prcs->args[0], "exit"))
	{
		if (all->prcs->rd)
		{
			printf("malloc_error_break: %p\n", all->prcs);
			exec_builting(all, all->prcs);
			free_char_array(&all->prcs->args);
			all->prcs->args = malloc(1);
			all->prcs->args[0] = NULL;
			return (0);
		}
		return (1);
	}
	return (0);
}

int	exec_builting(t_all *all, t_process *pcs)
{
	if (!all->prcs->args || !*all->prcs->args)
		return (0);
	if (ft_strcmp(pcs->args[0], "echo") == 0)
		return (ft_echo(pcs->args));
	if (ft_strcmp(pcs->args[0], "env") == 0)
		return (ft_env(all));
	if (ft_strcmp(pcs->args[0], "export") == 0)
		return (ft_export(pcs, all));
	if (ft_strcmp(pcs->args[0], "unset") == 0)
		return (ft_unset(pcs, all));
	if (ft_strcmp(pcs->args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(pcs->args[0], "cd") == 0)
		return (ft_cd(pcs, all));
	if (ft_strcmp(pcs->args[0], "exit") == 0)
		return (ft_exit(pcs, all));
	return (0);
}

int	is_builting(char *cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	executor_builting(t_all *all, t_process *process)
{
	if (process->args && is_builting(process->args[0]))
		exec_builting(all, process);
	free_char_array(&all->prcs->args);
	free_prcs_execve(all);
	actualize_env(all);
}
