/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 23:04:08 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/17 15:57:27 by vtrofyme         ###   ########.fr       */
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
	apply_redirs(shell, i);
	path_cmd = ft_get_path_command(cmd->args, cmd->envp);
	if (path_cmd)
	{
		execve(path_cmd, cmd->args, cmd->envp);
		free(path_cmd);
	}
	ft_error(2, cmd->args[0]);
	crit_except(shell, ER_CMD_NOT_FOUND);
}

static void	exec_one_cmd(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_or_exit(shell, 0);
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		ft_error(1, "fork");
}
