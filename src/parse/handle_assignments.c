/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_assignments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:40:23 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/24 17:43:43 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_assignments(t_cmd_p *cmd);

void	create_assignments(t_shell *shell, t_cmd_p *cmd)
{
	int	index;

	index = 0;
	cmd->ind_arg = 0;
	find_assignments(cmd);
	if (cmd->num_assign > 0)
	{
		cmd->assign = malloc(cmd->num_assign * sizeof(char *));
		if (cmd->assign == NULL)
			crit_except(shell, ER_MALLOC);
		nullify_array(cmd->assign, cmd->num_assign);
	}
	while (index < cmd->num_splits)
	{
		if (cmd->split_io[index] == IO_ASSIGN)
		{
			expand_dollars(shell, &(cmd->splits[index]),
				&(cmd->split_qs[index]));
			cmd->assign[cmd->ind_arg] = cmd->splits[index];
			(cmd->ind_arg)++;
		}
		index++;
	}
}

static void	find_assignments(t_cmd_p *cmd)
{
	int	index;
	int	flag_ass;

	index = 0;
	flag_ass = 1;
	while (index < cmd->num_splits)
	{
		if (cmd->split_io[index] == IO_KEEP)
		{
			if (flag_ass > 0)
				flag_ass = check_assignment(cmd->splits[index],
						cmd->split_qs[index]);
			if (flag_ass > 0)
			{
				cmd->split_io[index] = IO_ASSIGN;
				(cmd->num_assign)++;
			}
			else
				(cmd->num_args)++;
		}
		index++;
	}
}

void	transform_env(t_shell *shell, t_cmd *cmd)
{
	int	index;
	int	len;

	index = 0;
	while (index < cmd->num_assign)
	{
		len = 0;
		while (cmd->assign[index][len] && cmd->assign[index][len] != '=')
			len++;
		if (find_var_index(shell->envp, cmd->assign[index],
				shell->size_env, len) >= 0)
			replace_var_in_arr(shell, &(shell->envp),
				cmd->assign[index], &(shell->size_env));
		replace_var_in_arr(shell, &(shell->vars),
			cmd->assign[index], &(shell->size_vars));
		index++;
	}
}
