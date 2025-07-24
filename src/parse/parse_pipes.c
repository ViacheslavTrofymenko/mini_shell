/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:18:29 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/23 16:56:32 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_cmd(t_shell *shell, char *str, int index);
static void	count_pipes(t_shell *shell, char *str);

static void	count_pipes(t_shell *shell, char *str)
{
	int	index;

	index = 0;
	shell->num_cmds = 1;
	while (str[index])
	{
		if (str[index] == PIPE && shell->qts.q_marker_str[index] == Q_NORMAL)
			(shell->num_cmds)++;
		index++;
	}
}

void	create_cmd_vars(t_shell *shell, char *str)
{
	int	index;

	index = 0;
	shell->qts.ind_line = 0;
	shell->qts.ind_strt = 0;
	count_pipes(shell, str);
	shell->cmds = malloc ((shell->num_cmds) * sizeof(t_cmd));
	if (shell->cmds == NULL)
		crit_except(shell, ER_MALLOC);
	while (index < shell->num_cmds)
	{
		ft_bzero(&(shell->cmds[index]), sizeof(t_cmd));
		index++;
	}
	index = 0;
	while (str[index])
	{
		if (str[index] == PIPE && shell->qts.q_marker_str[index] == Q_NORMAL)
			create_cmd(shell, str, index);
		if ((str[index + 1] == '\0' && str[index] != PIPE))
			create_cmd(shell, str, index + 1);
		index++;
	}
}

static void	create_cmd(t_shell *shell, char *str, int index)
{
	(shell->cmd_p).line
		= malloc ((index - shell->qts.ind_strt + 1) * sizeof(char));
	(shell->cmd_p).q_type
		= malloc ((index - shell->qts.ind_strt + 1) * sizeof(char));
	if ((shell->cmd_p).line == NULL
		|| (shell->cmd_p).q_type == NULL)
		crit_except(shell, ER_MALLOC);
	ft_strlcpy((shell->cmd_p).line, &(str[shell->qts.ind_strt]),
		index - shell->qts.ind_strt + 1);
	ft_strlcpy((shell->cmd_p).q_type, &(shell->qts.q_marker_str[shell
			->qts.ind_strt]), index - shell->qts.ind_strt + 1);
	parse_cmd(shell, shell->qts.ind_line);
	shell->qts.ind_strt = index + 1;
	(shell->qts.ind_line)++;
}
