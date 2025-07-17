/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:43:17 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/17 17:02:07 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_input_redirs(t_shell *shell, int fd, int i, int j);
static void	apply_output_redirs(t_shell *shell, int i);

void	apply_redirs(t_shell *shell, int i)
{
	int		j;
	int		fd;
	t_cmd	*cmd;

	j = -1;
	fd = 0;
	cmd = &shell->cmds[i];
	while (++j < cmd->num_input)
		apply_input_redirs(shell, fd, i, j);
	apply_output_redirs(shell, j);
}

static void	apply_input_redirs(t_shell *shell, int fd, int i, int j)
{
	t_cmd	*cmd;

	cmd = &shell->cmds[i];
	if (cmd->in_types[j] == IO_SINGLE)
	{
		if (access(cmd->in_names[j], R_OK) == -1)
			crit_except(shell, ft_error(1, cmd->in_names[j]));
		fd = open(cmd->in_names[j], O_RDONLY);
		if (fd < 0)
			crit_except(shell, ft_error(1,  cmd->in_names[j]));
		if (dup2(fd, STDIN_FILENO) < 0)
			crit_except(shell, ft_error(1, "dup2 input"));
		close(fd);
	}
	else if (cmd->in_types[j] == IO_DOUBLE)
	{
		fd = open(cmd->in_names[j], O_RDONLY);
		if (fd < 0)
			crit_except(shell, ft_error(1, "heredoc temp file"));
		if (dup2(fd, STDIN_FILENO) < 0)
			crit_except(shell, ft_error(1, "dup2 heredoc"));
		close(fd);
		unlink(cmd->in_names[j]);
	}
}

static void	apply_output_redirs(t_shell *shell, int i)
{
	int		j;
	int		fd;
	t_cmd	*cmd;

	cmd = &shell->cmds[i];
	j = -1;
	while (++j < cmd->num_output)
	{
		if (cmd->out_types[j] == IO_SINGLE)
			fd = open(cmd->out_names[j], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			fd = open(cmd->out_names[j], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			crit_except(shell, ft_error(1, cmd->out_names[j]));
		if (dup2(fd, STDOUT_FILENO) < 0)
			crit_except(shell, ft_error(1, "dup2 output"));
		close(fd);
	}
}
