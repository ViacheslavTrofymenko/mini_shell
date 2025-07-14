/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:59:14 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/12 18:26:31 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_from_temp_to_cmd(t_shell *shell, int index);

void	parse_cmd(t_shell *shell, int index)
{
	count_splits(shell, &(shell->cmd_p));
	cmd_split(shell, &(shell->cmd_p));
	count_sources(&(shell->cmd_p));
	alloc_source_arrays(shell, &(shell->cmd_p));
	asign_sources(shell, &(shell->cmd_p));
	create_args(shell, &(shell->cmd_p));
	copy_from_temp_to_cmd(shell, index);
	clean_cmd_p(&(shell->cmd_p), M_PARTIAL);
	initialize_cmd_p(&(shell->cmd_p));
}

void	count_sources(t_cmd_p *cmd)
{
	int	index;

	index = 0;
	while (index < cmd->num_splits)
	{
		if (ft_strncmp(cmd->splits[index], "<", 1) == 0
			&& cmd->split_type[index] == Q_NORMAL)
			(cmd->num_input)++;
		if (ft_strncmp(cmd->splits[index], ">", 1) == 0
			&& cmd->split_type[index] == Q_NORMAL)
			(cmd->num_output)++;
		index++;
	}
	printf("Counted sources: %d %d\n", cmd->num_input, cmd->num_output);
}

void	alloc_source_arrays(t_shell *shell, t_cmd_p *cmd)
{
	int	index;

	index = -1;
	if (cmd->num_input > 0)
	{
		cmd->in_names = malloc(cmd->num_input * sizeof(char *));
		cmd->in_types = malloc(cmd->num_input * sizeof(char));
		if (cmd->in_names == NULL || cmd->in_types == NULL)
			crit_except(shell, ER_MALLOC);
		nullify_array(cmd->in_names, cmd->num_input);
	}
	if (cmd->num_output > 0)
	{
		cmd->out_names = malloc(cmd->num_output * sizeof(char *));
		cmd->out_types = malloc(cmd->num_output * sizeof(char));
		if (cmd->out_names == NULL || cmd->out_types == NULL)
			crit_except(shell, ER_MALLOC);
		nullify_array(cmd->out_names, cmd->num_output);
	}
	cmd->split_io = malloc(cmd->num_splits * sizeof(char));
	if (cmd->split_io == NULL)
		crit_except(shell, ER_MALLOC);
	while (++index < cmd->num_splits)
		cmd->split_io[index] = IO_KEEP;
}

void	create_args(t_shell *shell, t_cmd_p *cmd)
{
	int	index;

	index = 0;
	cmd->num_args = 0;
	while (index < cmd->num_splits)
	{
		if (cmd->split_io[index] == IO_KEEP)
			(cmd->num_args)++;
		index++;
	}
	cmd->args = malloc((cmd->num_args + 1) * sizeof(char *));
	if (cmd->args == NULL)
		crit_except(shell, ER_MALLOC);
	index = 0;
	cmd->ind_arg = 0;
	while (index < cmd->num_splits)
	{
		if (cmd->split_io[index] == IO_KEEP)
		{
			cmd->args[cmd->ind_arg] = cmd->splits[index];
			(cmd->ind_arg)++;
		}
		index++;
	}
	cmd->args[cmd->num_args] = NULL;
}

static void	copy_from_temp_to_cmd(t_shell *shell, int index)
{
	shell->cmds[index].args = shell->cmd_p.args;
	shell->cmds[index].in_names = shell->cmd_p.in_names;
	shell->cmds[index].out_names = shell->cmd_p.out_names;
	shell->cmds[index].in_types = shell->cmd_p.in_types;
	shell->cmds[index].out_types = shell->cmd_p.out_types;
	shell->cmds[index].num_args = shell->cmd_p.num_args;
	shell->cmds[index].num_input = shell->cmd_p.num_input;
	shell->cmds[index].num_output = shell->cmd_p.num_output;
	shell->cmds[index].error = shell->cmd_p.error;
	shell->cmds[index].er_synt_char = shell->cmd_p.er_synt_char;
}
