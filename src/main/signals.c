/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:08:09 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/09 16:29:54 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals(void)
{
	// struct sigaction	sa;

	// Configura el gestor de senyals per SIGQUIT per ignorar-lo
	signal(SIGQUIT, SIG_IGN);
	// Configura el gestor de senyals per SIGINT amb la funció ft_sig_ctr_c
	signal(SIGINT, ft_sig_ctr_c);

	// Configura el gestor de senyals per SIGINT amb la funció sigint_handler
	// sa.sa_handler = sigint_handler;
	// sa.sa_flags = SA_RESTART;
	// sigemptyset(&sa.sa_mask);
	// sigaction(SIGINT, &sa, NULL);
}

void	ft_sig_ctr_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// void	sigint_handler(int signo)
// {
// 	(void)signo;
// 	// Handler per SIGINT (Ctrl-C o Ctrl-D)
// 	printf("Fi de l'entrada (Ctrl-D detectat).\n");
// 	exit(0);
// }
