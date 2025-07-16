/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:33:59 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/14 14:14:00 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->cmds = NULL;
	shell->num_cmds = 0;
	shell->envp = envp;
	shell->qts.q_marker_str = NULL;
	shell->qts.str = NULL;
	initialize_cmd_p(&(shell->cmd_p));
}

void	initialize_cmd_p(t_cmd_p *cmd)
{
	cmd->args = NULL;
	cmd->line = NULL;
	cmd->q_type = NULL;
	cmd->in_names = NULL;
	cmd->in_types = NULL;
	cmd->out_names = NULL;
	cmd->out_types = NULL;
	cmd->splits = NULL;
	cmd->split_qs = NULL;
	cmd->split_io = NULL;
	cmd->num_input = 0;
	cmd->num_output = 0;
	cmd->num_splits = 0;
	cmd->num_args = 0;
	cmd->ind_arg = 0;
	cmd->ind_start = 0;
	cmd->len = 0;
	cmd->er_synt_char = NULL;
	cmd->error = 0;
}

void	initialize_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->in_names = NULL;
	cmd->in_types = NULL;
	cmd->out_names = NULL;
	cmd->out_types = NULL;
	cmd->num_input = 0;
	cmd->num_output = 0;
	cmd->er_synt_char = '\0';
	cmd->error = 0;
}

void	nullify_array(char	**arr, int size)
{
	int	index;

	index = 0;
	if (arr == NULL)
		return ;
	while (index < size)
	{
		arr[index] = NULL;
		index++;
	}
}
