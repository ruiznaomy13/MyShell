/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonpeat <mmonpeat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:08:09 by ncastell          #+#    #+#             */
/*   Updated: 2023/12/28 13:07:35 by mmonpeat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_signals(int mode)
{
	struct sigaction	signal;

	do_sigign(SIGINT);
	do_sigign(SIGQUIT);
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (mode == NORM)
		signal.sa_sigaction = norm_handler;
	else if (mode == N_INTERACT)
		signal.sa_sigaction = ninter_handler;
	else if (mode == HEREDOC)
		signal.sa_sigaction = heredoc_handler;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	return (0);
}

void	do_sigign(int signum)
{
	struct sigaction	signal;

	signal.sa_handler = SIG_IGN;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (sigaction(signum, &signal, NULL) < 0)
		exit (1);
}

void	norm_handler(int sig, siginfo_t *data, void *non_used_data)
{
	(void) data;
	(void) non_used_data;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_sig = 1;
	}
	return ;
}

void	ninter_handler(int sig, siginfo_t *data, void *non_used_data)
{
	(void) data;
	(void) non_used_data;
	if (sig == SIGINT)
		g_sig = 130;
	else if (sig == SIGQUIT)
		g_sig = 131;
	return ;
}

void	heredoc_handler(int sig, siginfo_t *data, void *non_used_data)
{
	(void) data;
	(void) non_used_data;
	if (sig == SIGINT)
	{
		g_sig = 1;
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		exit(1);
	}
	return ;
}
