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

void	count_sources(t_cmd *cmd)
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
}

void	alloc_source_arrays(t_shell *shell, t_cmd *cmd)
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

void	create_args(t_shell *shell, t_cmd *cmd)
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

void	expand_dollars(t_shell *shell, t_cmd *cmd)
{
	char	*temp;
	int		index;

	index = 0;
	temp = cmd->line;
	while (cmd->line[index])
	{
		if (cmd->line[index] == Q_DOLLAR && cmd->q_type[index] != Q_SINGLE)
		{
			cmd->ind_start = index;
			replace_variable(shell, cmd);
		}
		index++;
	}
}

/*void	replace_variable(t_shell *shell, t_cmd *cmd)
{
	int	index;

	index = cmd->ind_start;
	while (ft)
}*/