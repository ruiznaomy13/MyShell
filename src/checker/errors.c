/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:59:20 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/10/04 15:43:48 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	ft_error(int error)
{
	if (error == '\'' || error == '\"')
		printf("syntax error near unexpected token %c\n", error);
	else if (error == 5)
		printf("syntax error near unexpected token `newline'\n");
}
