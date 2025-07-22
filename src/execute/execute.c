/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 23:04:08 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/22 17:23:34 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_one_cmd(t_shell *shell);

void	execute_cmds(t_shell *shell)
{
	handle_heredocs(shell);
	if (!shell->cmds[0].args || !shell->cmds[0].args[0])
		return ;
	else if (shell->num_cmds == 1)
		exec_one_cmd(shell);
	else
		exec_pipe_cmds(shell);
}

void	exec_or_exit(t_shell *shell, int i)
{
	char	*path_cmd;
	t_cmd	*cmd;

	cmd = &shell->cmds[i];
	if (!cmd || !cmd->args[0] || cmd->args[0][0] == '\0')
		return ;
	path_cmd = ft_get_path_command(shell, i);
	if (path_cmd)
	{
		execve(path_cmd, cmd->args, cmd->envp);
		free(path_cmd);
	}
	ft_error(cmd->args[0]);
	crit_except(shell, ER_CMD_NOT_FOUND);
}

static void	exec_one_cmd(t_shell *shell)
{
	pid_t	pid;
	int		status;
	t_cmd	*cmd;

	cmd = &shell->cmds[0];
	if (check_builtin(cmd->args))
		run_builtin(shell, cmd->args);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			apply_redirs(shell, 0);
			exec_or_exit(shell, 0);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				shell->last_exit = WEXITSTATUS(status);
			else
				shell->last_exit = 1;
		}
		else
		{
			shell->last_exit = 1;
			ft_perror_custom("fork", errno);
		}
	}
}
