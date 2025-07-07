/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:59:09 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/07 16:56:03 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_string(t_shell *shell, int index, int type);
static void	handle_quote(t_shell *shell, int index, char quote_type, int mode);
static void	assign_parts(t_shell *shell, char *str);
static void	count_parts(t_shell *shell, char *str);

char	**parse_quotes(t_shell *shell, char *str)
{
	if (str == NULL)
		return (NULL);
	count_parts(shell, str);
	assign_parts(shell, str);
	return (shell->qts.result);
}

static void	count_parts(t_shell *shell, char *str)
{
	t_qoutes	*qts;
	int			ind;

	ind = 0;

	qts = &(shell->qts);
	qts->q_flag = Q_NORMAL;
	qts->num_splits = 0;
	qts->ind_line = 0;
	qts->ind_strt = 0;
	qts->str = str;
	while (str[ind] != '\0')
	{
		if (str[ind] == Q_SINGLE || str[ind] == Q_DOUBLE)
			handle_quote(shell, ind, str[ind], Q_M_CHECK);
		ind++;
	}
	if (qts->ind_strt < ind)
		handle_quote(shell, ind, Q_NORMAL, Q_M_CHECK);
}

static void	assign_parts(t_shell *shell, char *str)
{
	t_qoutes	*qts;
	int			ind;

	ind = 0;
	qts = &(shell->qts);
	qts->q_flag = Q_NORMAL;
	qts->ind_line = 0;
	qts->ind_strt = 0;
	qts->result = (char **)malloc((qts->num_splits + 1) * sizeof(char *));
	qts->types = (char *)malloc(qts->num_splits * sizeof(char));
	if (qts->result == NULL || qts->types == NULL)
		crit_except(shell, EXIT_FAILURE);
	qts->result[qts->num_splits] = NULL;
	while (str[ind] != '\0')
	{
		if (str[ind] == Q_SINGLE || str[ind] == Q_DOUBLE)
			handle_quote(shell, ind, str[ind], Q_M_WRITE);
		ind++;
	}
	if (qts->ind_strt < ind)
		handle_quote(shell, ind, Q_NORMAL, Q_M_WRITE);
}

static void	handle_quote(t_shell *shell, int index, char quote_type, int mode)
{
	t_qoutes	*qts;

	qts = &(shell->qts);
	if (qts->ind_strt < index && qts->q_flag == Q_NORMAL)
	{
		if (mode == Q_M_CHECK)
			(qts->num_splits)++;
		if (mode == Q_M_WRITE)
			create_string(shell, index, Q_NORMAL);
		qts->q_flag = quote_type;
	}
	else if (qts->q_flag == quote_type || quote_type == Q_NORMAL)
	{
		if (mode == Q_M_CHECK)
			(qts->num_splits)++;
		if (mode == Q_M_WRITE)
			create_string(shell, index, quote_type);
		qts->q_flag = Q_NORMAL;
		qts->ind_strt = index + 1;
	}

}

static void	create_string(t_shell *shell, int index, int type)
{
	t_qoutes	*qts;
	int			size;

	qts = &(shell->qts);
	size = index - qts->ind_strt + 2;
	if (type != Q_NORMAL)
		size -= 2;
	qts->result[qts->ind_line] = (char *)malloc(size * sizeof(char));
	if (qts->result[qts->ind_line] == NULL)
		crit_except(shell, EXIT_FAILURE);
	if (type == Q_NORMAL)
		ft_strlcpy(qts->result[qts->ind_line], &(qts->str[qts->ind_strt]),
			size - 1);
	else
		ft_strlcpy(qts->result[qts->ind_line], &(qts->str[qts->ind_strt + 1]),
			size - 1);
	qts->types[qts->ind_line] = type;
	qts->ind_strt = index + 1;
	(qts->ind_line)++;
}
