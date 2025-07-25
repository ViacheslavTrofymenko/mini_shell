/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:22:12 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/24 19:18:03 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_shell *shell, int prev_fd, int *pipe_fd, int i);
static void	wait_for_children(t_shell *shell, pid_t last_pid);
static void	exec_single_cmd(t_shell *shell, int i, int *prev_fd,
				pid_t *last_pid);

void	exec_pipe_cmds(t_shell *shell)
{
	int		i;
	int		prev_fd;
	pid_t	last_pid;

	i = 0;
	prev_fd = -1;
	last_pid = -1;
	while (i < shell->num_cmds)
	{
		exec_single_cmd(shell, i, &prev_fd, &last_pid);
		i++;
	}
	wait_for_children(shell, last_pid);
}

static void	exec_single_cmd(t_shell *shell, int i,
		int *prev_fd, pid_t *last_pid)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (i < shell->num_cmds - 1 && pipe(pipe_fd) == -1)
		crit_except(shell, ft_perror_custom("pipe", errno));
	pid = fork();
	if (pid == 0)
		child_process(shell, *prev_fd, pipe_fd, i);
	else if (i == shell->num_cmds - 1)
		*last_pid = pid;
	if (*prev_fd != -1)
		close(*prev_fd);
	if (i < shell->num_cmds - 1)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

static void	child_process(t_shell *shell, int prev_fd, int *pipe_fd, int i)
{
	t_cmd	*cmd;

	child_signal_handler();
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
		main_clean_exit(shell);
	}
	else
	{
		exec_or_exit(shell, i);
	}
}

static void	wait_for_children(t_shell *shell, pid_t last_pid)
{
	int	status;
	int	pid;

	pid = waitpid(-1, &status, 0);
	while (pid != -1)
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
		pid = waitpid(-1, &status, 0);
	}
}
