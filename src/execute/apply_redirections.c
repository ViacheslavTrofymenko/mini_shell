/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:43:17 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/18 14:58:33 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_input_redirs(t_shell *shell, int i, int j);
static void	apply_output_redirs(t_shell *shell, int i, int j);

void	apply_redirs(t_shell *shell, int i)
{
	int		j;
	t_cmd	*cmd;

	j = 0;
	cmd = &shell->cmds[i];
	while (j < cmd->num_files)
	{
		if (cmd->rw_type[j] == IO_INPUT)
			apply_input_redirs(shell, i, j);
		else if (cmd->rw_type[j] == IO_OUTPUT)
			apply_output_redirs(shell, i, j);
		j++;
	}
}

static void	apply_input_redirs(t_shell *shell, int i, int j)
{
	t_cmd	*cmd;
	int		fd;

	cmd = &shell->cmds[i];
	if (cmd->f_mode[j] == IO_SINGLE)
	{
		if (access(cmd->f_names[j], R_OK) == -1)
			crit_except(shell, ft_perror_custom(cmd->f_names[j], errno));
		fd = open(cmd->f_names[j], O_RDONLY);
		if (fd < 0)
			crit_except(shell, ft_perror_custom(cmd->f_names[j], errno));
		if (dup2(fd, STDIN_FILENO) < 0)
			crit_except(shell, ft_perror_custom("dup2 input", errno));
		close(fd);
	}
	else if (cmd->f_mode[j] == IO_DOUBLE)
	{
		fd = open(cmd->f_names[j], O_RDONLY);
		if (fd < 0)
			crit_except(shell, ft_perror_custom("heredoc temp file", errno));
		if (dup2(fd, STDIN_FILENO) < 0)
			crit_except(shell, ft_perror_custom("dup2 heredoc", errno));
		close(fd);
		unlink(cmd->f_names[j]);
	}
}

static void	apply_output_redirs(t_shell *shell, int i, int j)
{
	int		fd;
	t_cmd	*cmd;

	fd = 0;
	cmd = &shell->cmds[i];
	if (cmd->f_mode[j] == IO_SINGLE)
		fd = open(cmd->f_names[j], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (cmd->f_mode[j] == IO_DOUBLE)
		fd = open(cmd->f_names[j], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		crit_except(shell, ft_perror_custom(cmd->f_names[j], errno));
	if (dup2(fd, STDOUT_FILENO) < 0)
		crit_except(shell, ft_perror_custom("dup2 output", errno));
	close(fd);
}
