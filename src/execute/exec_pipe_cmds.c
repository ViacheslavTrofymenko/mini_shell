/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:22:12 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/22 23:06:55 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_shell *shell, int prev_fd, int *pipe_fd, int i);
static	void	wait_for_children(t_shell *shell, pid_t last_pid);

void	exec_pipe_cmds(t_shell *shell)
{
	int		i;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;

	i = 0;
	prev_fd = -1;
	last_pid = -1;
	while (i < shell->num_cmds)
	{
		if (i < shell->num_cmds - 1 && pipe(pipe_fd) == -1)
			crit_except(shell, ft_perror_custom("pipe", errno));
		pid = fork();
		if (pid == 0)
			child_process(shell, prev_fd, pipe_fd, i);
		else if (i == shell->num_cmds - 1)
			last_pid = pid;
		if (prev_fd != -1)
			close(prev_fd);
		if (i < shell->num_cmds - 1)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		i++;
	}
	wait_for_children(shell, last_pid);
}

void	child_process(t_shell *shell, int prev_fd, int *pipe_fd, int i)
{
	t_cmd	*cmd;

	cmd = &shell->cmds[i];
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
	apply_redirs(shell, i);
	if (check_builtin(cmd->args))
	{
		run_builtin(shell, cmd->args);
		exit(0);
	}
	else
	{
		exec_or_exit(shell, i);
	}
}

static void	wait_for_children(t_shell *shell, pid_t last_pid)
{
	int		status;
	pid_t	pid;

	while ((pid = waitpid(-1, &status, 0)) != -1)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->last_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->last_exit = 128 + WTERMSIG(status);
			else
				shell->last_exit = 1;
		}
	}
}
