/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:47:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/23 18:53:21 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_error_on_signal(t_shell *shell)
{
	if (g_last_signal != 0)
	{
		shell->last_exit = SIG_SHIFT + g_last_signal;
		g_last_signal = 0;
	}
}

void	child_signal_handler(void)
{
	struct sigaction	handler;

	ft_bzero(&handler, sizeof(handler));
	sigemptyset(&(handler.sa_mask));
	handler.sa_handler = SIG_DFL;
	handler.sa_flags = SA_RESETHAND;
	sigaction(SIGINT, &handler, NULL);
}
void	handle_ctrl_d(t_shell *shell)
{
	if (shell->cmd_line == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		main_clean_exit(shell);
	}
}
