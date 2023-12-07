/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:02:10 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/07 15:20:36 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	n_flag(char *s)
{
	int	i;

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

int	ft_echo(char **argv)
{
	int	skip_newline;
	int	i;

	skip_newline = 1;
	i = 0;
	if (!argv[1])
		return (1);
	while (n_flag(argv[skip_newline++]))
		i++;
	// printf("new line = %d == %d\n", i, skip_newline);
	while (argv[++i])
	{
		if (i != skip_newline - 1)
			printf(" ");
		printf("%s", argv[i]);
	}
	if (!n_flag(argv[1]))
		printf("\n");
	return (0);
}
