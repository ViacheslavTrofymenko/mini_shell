/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:59:09 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/24 18:37:14 by ikulik           ###   ########.fr       */
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

static void	handle_quote(t_shell *shell, int *index, char quote_type);

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
			handle_quote(shell, &ind, str[ind]);
		ind++;
	}
	shell->qts.q_marker_str[ind] = '\0';
}

static void	handle_quote(t_shell *shell, int *index, char quote_type)
{
	if (shell->qts.q_flag == Q_NORMAL)
	{
		shell->qts.q_marker_str[*index] = quote_type;
		shell->qts.q_flag = quote_type;
	}
	else if (shell->qts.q_flag == quote_type)
		shell->qts.q_flag = Q_NORMAL;
}

void	remove_quote_marks(char *str)
{
	int		index;
	char	q_flag;

	index = 0;
	q_flag = Q_NORMAL;
	if (str == NULL)
		return ;
	while (str[index])
	{
		if ((str[index] == Q_SINGLE || str[index] == Q_DOUBLE)
			&& (q_flag == Q_NORMAL || q_flag == str[index]))
		{
			if (q_flag == Q_NORMAL)
				q_flag = str[index];
			else
				q_flag = Q_NORMAL;
			ft_strcpy(&(str[index]), &(str[index + 1]));
			index--;
		}
		index++;
	}
}
