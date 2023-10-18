/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:06:05 by ncastell          #+#    #+#             */
/*   Updated: 2023/10/18 22:06:07 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int n_flag(char *s)
{
    int i;

    i = 1;
    if (s[0] == '-' && s[1] == 'n')
    {
        while (s[++i] != '\0')
        {
            if (s[i] != 'n')
                return (0);
        }
        return (1);
    }
    return (0);
}

int ft_echo(char **argv)
{
    int skip_newline;
    int i;
    if (!argv[1])
        return (1);
    skip_newline = n_flag(argv[1]);
    i = skip_newline;
    while (argv[++i])
    {
        if (i != skip_newline + 1)
            printf(" ");
        printf("%s", argv[i]);
    }
    if (!skip_newline)
        printf("\n");
    return (0);
}
