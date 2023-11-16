/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:08:09 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/16 20:24:37 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	ft_sig_ctr_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
}

void	signals(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sig_ctr_c);
}