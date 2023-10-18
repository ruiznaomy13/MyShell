/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:06:16 by ncastell          #+#    #+#             */
/*   Updated: 2023/10/18 22:17:37 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int ft_env(char **env)
{
    int i;

    i = -1;
    while (env[++i])
        printf("%s\n", env[i]);
    return (0);
}
