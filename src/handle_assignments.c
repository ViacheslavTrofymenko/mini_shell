/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_assignments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:40:23 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/18 23:40:23 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_assignments(t_shell *shell, t_cmd_p *cmd)
{
	int	index;
	int	flag_ass;

	index = 0;
	flag_ass = 1;
	while (index < cmd->num_splits && flag_ass > 0)
	{
		if (cmd->split_io[index] == IO_KEEP)
		{
			flag_ass = check_assignment(cmd->splits[index],
				cmd->split_qs[index]);
			if (flag_ass > 0)
			{
				cmd->split_io[index] = IO_ASSIGN;
				(cmd->num_assign)++;
			}
		}
		index++;
	}
}

void	create_assignments(t_shell *shell, t_cmd_p *cmd)
{
	int	index;

	index = 0;
	cmd->ind_arg = 0;
	cmd->assign = malloc(cmd->num_assign * sizeof(char *));
	if (cmd->assign == NULL)
		crit_except(shell, ER_MALLOC);
	nullify_array(cmd->assign, cmd->num_assign);
	while (index < cmd->num_assign)
	{
		if (cmd->split_io[index] == IO_ASSIGN)
		{
			cmd->assign[cmd->ind_arg] = cmd->splits[index];
			(cmd->ind_arg)++;
		}
		index++;
	}
}
