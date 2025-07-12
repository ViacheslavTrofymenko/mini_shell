/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 23:04:08 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/13 00:13:57 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_redirs(t_cmd *cmd);
static void	exec_or_exit(t_cmd *cmd);
static void	exec_one_cmd(t_cmd *cmd);

void	execute_cmds(t_shell *shell)
{
	if (shell->num_cmds == 1)
		exec_one_cmd(&shell->cmds[0]);
	else
		exec_pipe_cmds(shell);
}

static void	apply_redirs(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = -1;
	while (++i < cmd->num_input)
	{
		fd = open(cmd->in_names[i], O_RDONLY);
		if (fd < 0)
			exit(ft_error(2, cmd->in_names[i]));
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	i = -1;
	while (++i < cmd->num_output)
	{
		if (cmd->out_types[i] == IO_SINGLE)
			fd = open(cmd->out_names[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			fd = open(cmd->out_names[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			exit(ft_error(2, cmd->out_names[i]));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
static void	exec_or_exit(t_cmd *cmd)
{
	char *path_cmd;

	apply_redirs(cmd);
	path_cmd = ft_get_path_command(cmd->args, cmd->envp);
	if (path_cmd)
		execve(path_cmd, cmd->args, cmd->envp);
	ft_error(3, cmd->args[0]);
	exit(127);
}

static void	exec_one_cmd(t_cmd *cmd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		apply_redirs(cmd);
		exec_or_exit(cmd);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		ft_error(2, "fork");
}
