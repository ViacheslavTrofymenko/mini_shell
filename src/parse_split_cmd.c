/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:23:09 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/15 23:23:09 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	form_new_split(t_shell *shell, t_cmd_p *cmd, int index);
static void	update_synt_error(t_cmd_p *cmd, char *error);
static void	catch_syntax_error(t_cmd_p *cmd);

void	count_splits(t_shell *shell, t_cmd_p *cmd)
{
	int	ind;

	ind = 0;
	while (cmd->line[ind])
	{
		while (cmd->line[ind] && (ft_is_space(cmd->line[ind])
				&& cmd->q_type[ind] == Q_NORMAL))
			ind++;
		if (cmd->line[ind])
			(cmd->num_splits)++;
		while (ft_is_mol(cmd->line[ind]) && cmd->q_type[ind] == Q_NORMAL)
			ind++;
		while (cmd->line[ind] && !((cmd->q_type[ind] == Q_NORMAL && (ft_is_space
				(cmd->line[ind]) || ft_is_mol(cmd->line[ind])))))
			ind++;
	}
	printf("Splits: %d\n", cmd->num_splits);
	cmd->splits = malloc((cmd->num_splits + 1) * sizeof(char *));
	cmd->split_qs = malloc((cmd->num_splits + 1) * sizeof(char *));
	if (cmd->splits == NULL || cmd->split_qs == NULL)
		crit_except(shell, ER_MALLOC);
	nullify_array(cmd->splits, cmd->num_splits + 1);
	nullify_array(cmd->split_qs, cmd->num_splits + 1);
}

void	cmd_split(t_shell *shell, t_cmd_p *cmd)
{
	int	ind;

	ind = 0;
	cmd->ind_arg = 0;
	while (cmd->line[ind])
	{
		while (cmd->line[ind] && (ft_is_space(cmd->line[ind])
				&& cmd->q_type[ind] == Q_NORMAL))
			ind++;
		cmd->ind_start = ind;
		while (ft_is_mol(cmd->line[ind]) && cmd->q_type[ind] == Q_NORMAL)
			ind++;
		while (cmd->line[ind] && !(cmd->q_type[ind] == Q_NORMAL
				&& (ft_is_space(cmd->line[ind])
				|| ft_is_mol(cmd->line[ind]))))
			ind++;
		if (ind > cmd->ind_start)
			form_new_split(shell, cmd, ind);
	}
	catch_syntax_error(cmd);
}

static void	form_new_split(t_shell *shell, t_cmd_p *cmd, int index)
{
	int	size;

	size = index - cmd->ind_start + 1;
	cmd->splits[cmd->ind_arg] = malloc (size * sizeof(char));
	cmd->split_qs[cmd->ind_arg] = malloc (size * sizeof(char));
	if (cmd->splits[cmd->ind_arg] == NULL
			|| cmd->split_qs[cmd->ind_arg] == NULL)
		crit_except(shell, ER_MALLOC);
	ft_strlcpy(cmd->splits[cmd->ind_arg], &(cmd->line[cmd->ind_start]), size);
	ft_strlcpy(cmd->split_qs[cmd->ind_arg],
			&(cmd->q_type[cmd->ind_start]), size);
	(cmd->ind_arg)++;
}

static void	catch_syntax_error(t_cmd_p *cmd)
{
	int	ind_sp;
	int	ind;

	ind_sp = 0;
	while (ind_sp < cmd->num_splits)
	{
		ind = 0;
		if (ft_is_mol(cmd->splits[ind_sp][0]) && cmd->split_qs[ind_sp][0] == Q_NORMAL)
		{
			ind++;
			if (cmd->splits[ind_sp][1] == cmd->splits[ind_sp][0])
				ind++;
			if (ft_is_mol(cmd->splits[ind_sp][ind])
					&& cmd->split_qs[ind_sp][ind] == Q_NORMAL)
				update_synt_error(cmd, &(cmd->splits[ind_sp][ind]));
			if (cmd->splits[ind_sp][ind] == '\0'
					&& ind_sp == cmd->num_splits - 1)
				update_synt_error(cmd, &(cmd->splits[ind_sp][ind]));
			if (cmd->splits[ind_sp][ind] == '\0' && ind_sp < cmd->num_splits - 1
					&& ft_is_mol(cmd->splits[ind_sp + 1][0])
					&& cmd->split_qs[ind_sp + 1][0] == Q_NORMAL)
				update_synt_error(cmd, &(cmd->splits[ind_sp + 1][0]));
		}
		ind_sp++;
	}
}

static void	update_synt_error(t_cmd_p *cmd, char *error)
{
	cmd->error |= ER_SYNTAX;
	if (cmd->er_synt_char == NULL)
		cmd->er_synt_char = error;
}
