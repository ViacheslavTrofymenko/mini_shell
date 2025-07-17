/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:43:17 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/17 14:21:03 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_input_redirs(t_cmd *cmd, int fd, int i);
static void	apply_output_redirs(t_cmd *cmd);

void	apply_redirs(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = -1;
	fd = 0;
	while (++i < cmd->num_input)
		apply_input_redirs(cmd, fd, i);
	apply_output_redirs(cmd);
}

static void	apply_input_redirs(t_cmd *cmd, int fd, int i)
{
	if (cmd->in_types[i] == IO_SINGLE)
	{
		fd = open(cmd->in_names[i], O_RDONLY);
		if (fd < 0)
			exit(ft_error(1, cmd->in_names[i]));
		if (dup2(fd, STDIN_FILENO) < 0)
			exit(ft_error(1, "dup2 input"));
		close(fd);
	}
	else if (cmd->in_types[i] == IO_DOUBLE)
	{
		fd = open(cmd->in_names[i], O_RDONLY);
		if (fd < 0)
			exit(ft_error(1, "heredoc temp file"));
		if (dup2(fd, STDIN_FILENO) < 0)
			exit(ft_error(1, "dup2 heredoc"));
		close(fd);
		unlink(cmd->in_names[i]);
	}
}

static void	apply_output_redirs(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = -1;
	while (++i < cmd->num_output)
	{
		if (cmd->out_types[i] == IO_SINGLE)
			fd = open(cmd->out_names[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			fd = open(cmd->out_names[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			exit(ft_error(1, cmd->out_names[i]));
		if (dup2(fd, STDOUT_FILENO) < 0)
			exit(ft_error(1, "dup2 output"));
		close(fd);
	}
}
