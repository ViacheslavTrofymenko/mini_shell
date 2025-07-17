/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:08:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/17 18:03:09 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_one_cmd(t_cmd *cmd);
static void	clean_double_arr(char **arr, int size);
static void	safe_free(char **s);
void		clean_unused_splits(t_cmd_p *cmd);

void	clean_cmds(t_shell *shell)
{
	int	index;

	index = 0;
	if (shell->cmds == NULL)
		return ;
	while (index < shell->num_cmds)
	{
		clean_one_cmd(&(shell->cmds[index]));
		index++;
	}
	free(shell->cmds);
	shell->cmds = NULL;
	shell->num_cmds = 0;
}

void	clean_cmd_p(t_cmd_p *cmd, int mode)
{
	if (cmd == NULL)
		return ;
	safe_free(&(cmd->line));
	safe_free(&(cmd->q_type));
	if (mode == M_PARTIAL)
		clean_unused_splits(cmd);
	safe_free(&(cmd->split_io));
	if (mode == M_TOTAL)
	{
		safe_free(&(cmd->f_mode));
		safe_free(&(cmd->rw_type));
		clean_double_arr(cmd->f_names, cmd->num_files);
		clean_double_arr(cmd->splits, cmd->num_splits);
	}
}

void	clean_unused_splits(t_cmd_p *cmd)
{
	int	index;

	index = 0;
	if (cmd->split_io == NULL)
		return ;
	while (index < cmd->num_splits)
	{
		if (cmd->split_io[index] == IO_REMOVE)
		{
			safe_free(&(cmd->splits[index]));
			cmd->splits[index] = NULL;
		}
		safe_free(&(cmd->split_qs[index]));
		index++;
	}
	free(cmd->splits);
	free(cmd->split_qs);
}

static void	clean_one_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	safe_free(&(cmd->f_mode));
	safe_free(&(cmd->rw_type));
	clean_double_arr(cmd->args, cmd->num_args);
	clean_double_arr(cmd->f_names, cmd->num_input);
}

static void	clean_double_arr(char **arr, int size)
{
	int	index;

	index = 0;
	if (arr == NULL)
		return ;
	while (index < size)
	{
		if (arr[index] != NULL)
			safe_free(&(arr[index]));
		index++;
	}
	free(arr);
}

static void	safe_free(char **s)
{
	if (s != NULL && *s != NULL)
	{
		free(*s);
		*s = NULL;
	}
}
