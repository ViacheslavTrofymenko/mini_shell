/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:14:37 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/22 20:14:37 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_interactive(int signal);
static void	sigint_noninteractive(int signal);

void	interactive_signal_handler(void)
{
	struct sigaction	handler;

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
	sigaddset(&(handler.sa_mask), SIGQUIT);
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
	}
}
static void	sigint_noninteractive(int signal)
{
	if (signal == SIGINT)
	{
		interactive_signal_handler();
		kill(0, SIGINT);
	}
}

void	handle_ctrl_d(t_shell *shell)
{
	if (shell->cmd_line == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		main_clean_exit(shell);
	}
}