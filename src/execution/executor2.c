/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:18:35 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/12/09 15:48:36 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

int	exec_builting(t_all *all, t_process *pcs)
{
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
}
