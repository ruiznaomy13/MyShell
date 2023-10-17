/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:18:35 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/10/17 22:53:13 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    size_t i = 0;

    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;
    return (unsigned char)(s1[i]) - (unsigned char)(s2[i]);
}

void builting_echo(char **av, char **env)
{
    (void)env;
    int i = 0;
    while (av[++i])
        printf("%s ", av[i]);
}

int exec_builting(t_process *pcs, char **env)
{
    if (ft_strcmp(pcs->args[0], "echo") == 0)
        builting_echo(pcs->args, env);
    return (0);
}

int is_builting(char *cmd)
{
    if (ft_strcmp(cmd, "echo") == 0)
        return (1);
    return (0);
}

void executor_builting(t_all *all)
{
	printf("EJECTUTOR\n");
    if (all->prcs->args && is_builting(all->prcs->args[0]))
        exec_builting(all->prcs, all->env);
}