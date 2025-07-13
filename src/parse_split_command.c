/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:40:47 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/12 17:46:06 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_quotes(t_cmd_p *cmd, int *flag_sp, int *index);
static void	form_qted_str(t_shell *shell, t_cmd_p *cmd, int *index, int *flag);
static void	form_normal_str(t_shell *shell, t_cmd_p *cmd, int *flag);

void	count_splits(t_shell *shell, t_cmd_p *cmd)
{
	int		flag_sp;
	int		index;

	flag_sp = 1;
	index = -1;
	while (cmd->line[++index])
	{
		if (cmd->q_type[index] != Q_NORMAL)
		{
			skip_quotes(cmd, &flag_sp, &index);
			continue ;
		}
		if (flag_sp && ft_is_space(cmd->line[index]))
		{
			flag_sp = 0;
			(cmd->num_splits)++;
		}
		if (ft_is_space(cmd->line[index]) == 0)
			flag_sp = 1;
	}
	cmd->splits = malloc((cmd->num_splits + 1) * sizeof(char *));
	cmd->split_type = malloc((cmd->num_splits + 1) * sizeof(char));
	if (cmd->splits == NULL || cmd->split_type == NULL)
		crit_except(shell, ER_MALLOC);
}

static void	skip_quotes(t_cmd_p *cmd, int *flag_sp, int *index)
{
	char	q_type;

	q_type = cmd->q_type[*index];
	if (q_type != Q_NORMAL)
	{
		(*index)++;
		while (cmd->line[*index] && cmd->line[*index] != q_type)
			(*index)++;
		(*index)++;
		(cmd->num_splits)++;
		*flag_sp = 1;
	}
}

void	cmd_split(t_shell *shell, t_cmd_p *cmd)
{
	int	flag;
	int	index;

	index = 0;
	flag = 1;
	nullify_array(cmd->splits, cmd->num_splits + 1);
	while (cmd->line[index])
	{
		if (cmd->q_type[index] != Q_NORMAL)
		{
			form_qted_str(shell, cmd, &index, &flag);
			continue ;
		}
		if (flag == 1 && ft_is_space(cmd->line[index]))
		{
			flag = 0;
			cmd->ind_start = index;
		}
		if (flag == 0 && ft_is_space(cmd->line[index]))
			(cmd->len)++;
		if ((flag == 0 && ft_is_space(cmd->line[index]) == 0)
			|| cmd->line[index + 1] == '\0')
			form_normal_str(shell, cmd, &flag);
		index++;
	}
}

static void	form_normal_str(t_shell *shell, t_cmd_p *cmd, int *flag)
{
	cmd->splits[cmd->ind_arg] = malloc((cmd->len + 1) * sizeof(char));
	if (cmd->splits[cmd->ind_arg] == NULL)
		crit_except(shell, ER_MALLOC);
	ft_strlcpy(cmd->splits[cmd->ind_arg],
		&(cmd->line[cmd->ind_start]), cmd->len + 1);
	cmd->split_type[cmd->ind_arg] = Q_NORMAL;
	(cmd->ind_arg)++;
	*flag = 1;
	cmd->len = 0;
}

static void	form_qted_str(t_shell *shell, t_cmd_p *cmd, int *index, int *flag)
{
	char	q_type;
	int		size;

	q_type = cmd->q_type[*index];
	if (cmd->len > 0)
		form_normal_str(shell, cmd, flag);
	cmd->ind_start = *index;
	(*index)++;
	while (cmd->line[*index] && cmd->line[*index] != q_type)
		(*index)++;
	(*index)++;
	size = *index - cmd->ind_start - 1;
	cmd->splits[cmd->ind_arg] = malloc(size * sizeof(char));
	if (cmd->splits[cmd->ind_arg] == NULL)
		crit_except(shell, ER_MALLOC);
	ft_strlcpy(cmd->splits[cmd->ind_arg], &(cmd->line[cmd->ind_start + 1]),
		size);
	cmd->split_type[cmd->ind_arg] = q_type;
	(cmd->ind_arg)++;
	cmd->ind_start = *index + 1;
	*flag = 1;
}
