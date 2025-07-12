/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:08:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/12 17:56:16 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_cmds(t_shell *shell);
static void	clean_cmd(t_cmd *cmd);
static void	clean_double_arr(char **arr, int size);
static void	safe_free(void *s);

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
	safe_free(cmd->line);
	safe_free(cmd->q_type);
	safe_free(cmd->split_type);
	safe_free(cmd->split_io);
	safe_free(cmd->in_types);
	safe_free(cmd->out_types);
	clean_double_arr(cmd->splits, cmd->num_splits);
	clean_double_arr(cmd->in_names, cmd->num_input);
	clean_double_arr(cmd->out_names, cmd->num_output);
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
			free(arr[index]);
		index++;
	}
	free(arr);
}

static void	safe_free(void *s)
{
	if (s != NULL)
		free(s);
}
