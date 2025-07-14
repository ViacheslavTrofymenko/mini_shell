/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:59:14 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/12 18:05:23 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	next_input_split(t_shell *shell, t_cmd *cmd, int index, int ind_input);
void	next_output_split(t_shell *shell, t_cmd *cmd, int index, int ind_input);
void	create_output_name(t_shell *shell, t_cmd *cmd, int index);
void	create_input_name(t_shell *shell, t_cmd *cmd, int index);

void	asign_sources(t_shell *shell, t_cmd *cmd)
{
	int	index;

	index = 0;
	count_sources(cmd);
	alloc_source_arrays(shell, cmd);
	cmd->ind_arg = 0;
	cmd->ind_start = 0;
	while (index < cmd->num_splits)
	{
		if (ft_strncmp(cmd->splits[index], "<", 1) == 0
			&& cmd->split_type[index] == Q_NORMAL)
			create_input_name(shell, cmd, index);
		if (ft_strncmp(cmd->splits[index], ">", 1) == 0
			&& cmd->split_type[index] == Q_NORMAL)
			create_output_name(shell, cmd, index);
		index++;
	}
}

void	create_input_name(t_shell *shell, t_cmd *cmd, int index)
{
	int			start;
	int			size;

	start = 1;
	cmd->in_types[cmd->ind_start] = IO_SINGLE;
	cmd->split_io[index] = IO_REMOVE;
	if (ft_strncmp(cmd->splits[index], "<<", 2) == 0)
	{
		cmd->in_types[cmd->ind_start] = IO_DOUBLE;
		start = 2;
	}
	size = ft_strlen(cmd->splits[index]);
	if (size > start)
	{
		cmd->in_names[cmd->ind_start] = malloc((size - start + 1)
				* sizeof(char));
		if (cmd->in_names[cmd->ind_start] == NULL)
			crit_except(shell, ER_MALLOC);
		ft_strlcpy(cmd->in_names[cmd->ind_start], &(cmd->splits[index][start]),
			size - start + 1);
	}
	else
		next_input_split(shell, cmd, index, cmd->ind_start);
	(cmd->ind_start)++;
}

void	next_input_split(t_shell *shell, t_cmd *cmd, int index, int ind_input)
{
	int	len;

	if (index == cmd->num_splits - 1
		|| ft_strncmp(cmd->splits[index + 1], "<", 1) == 0)
	{
		cmd->error |= ER_SYNTAX;
		if (cmd->er_synt_char != '\0')
			cmd->er_synt_char = '<';
		return ;
	}
	len = ft_strlen(cmd->splits[index + 1]);
	cmd->in_names[ind_input] = malloc((len + 1) * sizeof(char));
	if (cmd->in_names[ind_input] == NULL)
		crit_except(shell, ER_MALLOC);
	ft_strlcpy(cmd->in_names[ind_input], cmd->splits[index + 1], len + 1);
	cmd->split_io[index + 1] = IO_REMOVE;
}

void	create_output_name(t_shell *shell, t_cmd *cmd, int index)
{
	int			start;
	int			size;

	start = 1;
	cmd->out_types[cmd->ind_arg] = IO_SINGLE;
	cmd->split_io[index] = IO_REMOVE;
	if (ft_strncmp(cmd->splits[index], ">>", 2) == 0)
	{
		cmd->out_types[cmd->ind_arg] = IO_DOUBLE;
		start = 2;
	}
	size = ft_strlen(cmd->splits[index]);
	if (size > start)
	{
		cmd->out_names[cmd->ind_arg] = malloc((size - start + 1)
				* sizeof(char));
		if (cmd->out_names[cmd->ind_arg] == NULL)
			crit_except(shell, ER_MALLOC);
		ft_strlcpy(cmd->out_names[cmd->ind_arg], &(cmd->splits[index][start]),
			size - start + 1);
	}
	else
		next_output_split(shell, cmd, index, cmd->ind_arg);
	(cmd->ind_arg)++;
}

void	next_output_split(t_shell *shell, t_cmd *cmd, int index, int ind_output)
{
	int	len;

	if (index == cmd->num_splits - 1
		|| ft_strncmp(cmd->splits[index + 1], ">", 1) == 0)
	{
		cmd->error |= ER_SYNTAX;
		if (cmd->er_synt_char != '\0')
			cmd->er_synt_char = '>';
		return ;
	}
	len = ft_strlen(cmd->splits[index + 1]);
	cmd->out_names[ind_output] = malloc((len + 1) * sizeof(char));
	if (cmd->out_names[ind_output] == NULL)
		crit_except(shell, ER_MALLOC);
	ft_strlcpy(cmd->out_names[ind_output], cmd->splits[index + 1], len + 1);
	cmd->split_io[index + 1] = IO_REMOVE;
}
