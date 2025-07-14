/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:59:09 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/12 23:00:41 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Splits string into NULL-terminated array of
 * partitions. qts->types contains types ', " or normal.
 * Unclosed quotes are considered regular chars.
 *
 * @param shell	Metadata struct
 * @param str	Input string
 * @param qts	Quotes-parsing struct
 * @return		Pointer to the array of strings
 */


static void	handle_quote(t_shell *shell, int index, char quote_type);
static void	create_cmd(t_shell *shell, char *str, int index);

void	mark_quotes(t_shell *shell, char *str)
{
	t_qoutes	*qts;
	int			ind;

	ind = 0;
	qts = &(shell->qts);
	if (str == NULL)
		return ;
	qts->q_flag = Q_NORMAL;
	shell->qts.q_marker_str = malloc(((ft_strlen(str)) + 1) * sizeof(char));
	if (shell->qts.q_marker_str == NULL)
		crit_except(shell, ER_MALLOC);
	shell->qts.q_marker_str[ft_strlen(str)] = '\0';
	qts->str = str;
	while (str[ind] != '\0')
	{
		shell->qts.q_marker_str[ind] = shell->qts.q_flag;
		if (str[ind] == Q_SINGLE || str[ind] == Q_DOUBLE)
			handle_quote(shell, ind, str[ind]);
		ind++;
	}
}

static void	handle_quote(t_shell *shell, int index, char quote_type)
{
	if (shell->qts.q_flag == Q_NORMAL)
	{
		shell->qts.q_marker_str[index] = quote_type;
		shell->qts.q_flag = quote_type;
	}
	else if (shell->qts.q_flag == quote_type)
	{
		shell->qts.q_marker_str[index] = quote_type;
		shell->qts.q_flag = Q_NORMAL;
	}
}

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
		initialize_cmd(&(shell->cmds[index]));
		index++;
	}
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
