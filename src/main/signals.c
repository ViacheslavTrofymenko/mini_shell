/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:14:37 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/23 19:04:13 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_interactive(int signal);
static void	sigint_noninteractive(int signal);

void	interactive_signal_handler(void)
{
	struct sigaction	handler;

	g_last_signal = 0;
	ft_bzero(&handler, sizeof(handler));
	sigemptyset(&(handler.sa_mask));
	sigaddset(&(handler.sa_mask), SIGINT);
	sigaddset(&(handler.sa_mask), SIGQUIT);
	handler.sa_handler = &sigint_interactive;
	sigaction(SIGINT, &handler, NULL);
}

void	noninteractive_signal_handler(void)
{
	struct sigaction	handler;

	ft_bzero(&handler, sizeof(handler));
	sigemptyset(&(handler.sa_mask));
	sigaddset(&(handler.sa_mask), SIGINT);
	handler.sa_handler = &sigint_noninteractive;
	sigaction(SIGINT, &handler, NULL);
}

static void	sigint_interactive(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_last_signal = SIGINT;
	}
}

static void	sigint_noninteractive(int signal)
{
	struct sigaction	handler;

	ft_bzero(&handler, sizeof(handler));
	sigemptyset(&(handler.sa_mask));
	handler.sa_handler = SIG_IGN;
	sigaction(SIGINT, &handler, NULL);
	if (signal == SIGINT)
	{
		printf("\n");
		g_last_signal = SIGINT;
		kill(0, SIGINT);
	}
}

void	sigterm_handler(void)
{
	struct sigaction	handler;

	ft_bzero(&handler, sizeof(handler));
	sigemptyset(&(handler.sa_mask));
	sigaddset(&(handler.sa_mask), SIGTERM);
	handler.sa_handler = SIG_IGN;
	sigaction(SIGTERM, &handler, NULL);
}
