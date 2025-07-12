/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:08:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/11 20:08:19 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_cmds(t_shell *shell);
static void	clean_cmd(t_cmd *cmd);

void	crit_except(t_shell *data, int error_code)
{
	int	index;

	index = 0;
	if (data->qts.str != NULL)
		free(data->qts.str);
	if (data->qts.q_marker_str != NULL)
		free(data->qts.q_marker_str);
	clean_cmds(data);
	if (error_code != 0)
		exit (error_code);
}

static void	clean_cmds(t_shell *shell)
{
	int	index;

	index = 0;
	if (shell->cmds == NULL)
		return ;
	while (index < shell->num_cmds)
	{
		clean_cmd(&(shell->cmds[index]));
		index++;
	}
	free(shell->cmds);
	shell->cmds = NULL;
	shell->num_cmds = 0;
}

static void	clean_cmd(t_cmd *cmd)
{
	int	index;

	index = 0;
	if (cmd == NULL)
		return ;
	if (cmd->line != NULL)
		free(cmd->line);
	if (cmd->q_type != NULL)
		free(cmd->q_type);
	if (cmd->split_type != NULL)
		free(cmd->split_type);
	if (cmd->splits != NULL)
	{
		while (index < cmd->num_splits)
		{
			if (cmd->splits[index] != NULL)
				free(cmd->splits[index]);
			index++;
		}
		free(cmd->splits);
	}
}
