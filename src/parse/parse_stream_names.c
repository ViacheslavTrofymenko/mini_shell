/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stream_names.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:59:14 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/24 18:27:36 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	next_input_split(t_shell *shell, t_cmd_p *cmd, int index, int ind_inp);
void	next_output_split(t_shell *shell, t_cmd_p *cmd, int index, int ind_inp);
void	create_output_name(t_shell *shell, t_cmd_p *cmd, int index);
void	create_input_name(t_shell *shell, t_cmd_p *cmd, int index);

void	asign_sources(t_shell *shell, t_cmd_p *cmd)
{
	int	index;

	index = 0;
	cmd->ind_arg = 0;
	while (index < cmd->num_splits)
	{
		if (cmd->splits[index][0] == '<' && cmd->split_qs[index][0] == Q_NORMAL)
		{
			cmd->split_io[index] = IO_REMOVE;
			create_input_name(shell, cmd, index);
			(cmd->ind_arg)++;
		}
		if (cmd->splits[index][0] == '>' && cmd->split_qs[index][0] == Q_NORMAL)
		{
			cmd->split_io[index] = IO_REMOVE;
			create_output_name(shell, cmd, index);
			(cmd->ind_arg)++;
		}
		index++;
	}
}

void	create_input_name(t_shell *shell, t_cmd_p *cmd, int index)
{
	int			start;
	int			size;

	start = 1;
	cmd->f_mode[cmd->ind_arg] = IO_SINGLE;
	cmd->rw_type[cmd->ind_arg] = IO_INPUT;
	if (cmd->splits[index][1] == '<' && cmd->split_qs[index][1] == Q_NORMAL)
		cmd->f_mode[cmd->ind_arg] = IO_DOUBLE;
	start += (cmd->f_mode[cmd->ind_arg] == IO_DOUBLE);
	size = ft_strlen(cmd->splits[index]);
	if (cmd->f_mode[cmd->ind_arg] == IO_SINGLE)
		expand_dollars(shell, &(cmd->splits[index]), &(cmd->split_qs[index]));
	else
		remove_quote_marks(cmd->splits[index]);
	if (size > start)
	{
		size = ft_strlen(cmd->splits[index]);
		cmd->f_names[cmd->ind_arg] = malloc((size - start + 1) * sizeof(char));
		if (cmd->f_names[cmd->ind_arg] == NULL)
			crit_except(shell, ER_MALLOC);
		ft_strlcpy(cmd->f_names[cmd->ind_arg], &(cmd->splits[index][start]),
			size - start + 1);
	}
	else
		next_input_split(shell, cmd, index, cmd->ind_arg);
}

void	next_input_split(t_shell *shell, t_cmd_p *cmd, int index, int ind_input)
{
	int	len;

	if (index == cmd->num_splits - 1)
		return ;
	if (cmd->f_mode[cmd->ind_arg] == IO_SINGLE)
		expand_dollars(shell, &(cmd->splits[index + 1]),
			&(cmd->split_qs[index + 1]));
	else
		remove_quote_marks(cmd->splits[index + 1]);
	len = ft_strlen(cmd->splits[index + 1]);
	cmd->f_names[ind_input] = malloc((len + 1) * sizeof(char));
	if (cmd->f_names[ind_input] == NULL)
		crit_except(shell, ER_MALLOC);
	ft_strlcpy(cmd->f_names[ind_input], cmd->splits[index + 1], len + 1);
	cmd->split_io[index + 1] = IO_REMOVE;
}

void	create_output_name(t_shell *shell, t_cmd_p *cmd, int index)
{
	int			start;
	int			size;

	start = 1;
	cmd->f_mode[cmd->ind_arg] = IO_SINGLE;
	cmd->rw_type[cmd->ind_arg] = IO_OUTPUT;
	if (cmd->splits[index][1] == '>' && cmd->split_qs[index][1] == Q_NORMAL)
		cmd->f_mode[cmd->ind_arg] = IO_DOUBLE;
	if (cmd->f_mode[cmd->ind_arg] == IO_DOUBLE)
		start = 2;
	size = ft_strlen(cmd->splits[index]);
	expand_dollars(shell, &(cmd->splits[index]), &(cmd->split_qs[index]));
	if (size > start)
	{
		size = ft_strlen(cmd->splits[index]);
		cmd->f_names[cmd->ind_arg] = malloc((size - start + 1)
				* sizeof(char));
		if (cmd->f_names[cmd->ind_arg] == NULL)
			crit_except(shell, ER_MALLOC);
		ft_strlcpy(cmd->f_names[cmd->ind_arg], &(cmd->splits[index][start]),
			size - start + 1);
	}
	else
		next_output_split(shell, cmd, index, cmd->ind_arg);
}

void	next_output_split(t_shell *shell, t_cmd_p *cmd, int index, int ind_out)
{
	int	len;

	if (index == cmd->num_splits - 1)
		return ;
	expand_dollars(shell, &(cmd->splits[index + 1]),
		&(cmd->split_qs[index + 1]));
	len = ft_strlen(cmd->splits[index + 1]);
	cmd->f_names[ind_out] = malloc((len + 1) * sizeof(char));
	if (cmd->f_names[ind_out] == NULL)
		crit_except(shell, ER_MALLOC);
	ft_strlcpy(cmd->f_names[ind_out], cmd->splits[index + 1], len + 1);
	cmd->split_io[index + 1] = IO_REMOVE;
}
