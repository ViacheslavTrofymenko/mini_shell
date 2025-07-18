/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:22:12 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/18 14:51:21 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_shell *shell, int prev_fd, int *pipe_fd, int i);

void	exec_pipe_cmds(t_shell *shell)
{
	int		i;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	i = 0;
	prev_fd = -1;
	while (i < shell->num_cmds)
	{
		if (i < shell->num_cmds - 1 && pipe(pipe_fd) == -1)
			crit_except(shell, ft_perror_custom("pipe", errno));
		pid = fork();
		if (pid == 0)
			child_process(shell, prev_fd, pipe_fd, i);
		if (prev_fd != -1)
			close(prev_fd);
		if (i < shell->num_cmds - 1)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		i++;
	}
	while (waitpid(-1, NULL, 0) != -1)
		continue ;
}

void	child_process(t_shell *shell, int prev_fd, int *pipe_fd, int i)
{
	if (i > 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i < shell->num_cmds -1)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	exec_or_exit(shell, i);
}
