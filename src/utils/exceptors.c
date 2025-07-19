/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:43:40 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/17 19:03:02 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	crit_except(t_shell *data, int error_code)
{
	if (data->qts.str != NULL)
		free(data->qts.str);
	data->qts.str = NULL;
	if (data->qts.q_marker_str != NULL)
		free(data->qts.q_marker_str);
	data->qts.q_marker_str = NULL;
	clean_cmds(data);
	clean_cmd_p(&(data->cmd_p), M_TOTAL);
	if (error_code != 0)
		exit (error_code);
}

void	correct_syntax_error(t_shell *shell, int index)
{
	shell->cmds[index].er_synt_char = *(shell->cmd_p.er_synt_char);
	if (*(shell->cmd_p.er_synt_char) == '\0')
	{
		if (index < shell->num_cmds - 1)
			shell->cmds[index].er_synt_char = '|';
		else
			shell->cmds[index].er_synt_char = '\n';
	}
}

int	check_syntax_except(t_shell *shell)
{
	int	index;

	index = 0;
	while(index < shell->num_cmds)
	{
		if (shell->cmds[index].error & ER_SYNTAX)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			if (shell->cmds[index].er_synt_char == '\n')
				ft_putendl_fd("newline'", 2);
			else
			{
				ft_putchar_fd(shell->cmds[index].er_synt_char, 2);
				ft_putendl_fd("'", 2);
			}
			shell->last_exit = ER_SYNTAX;
			return (EXIT_FAILURE);
		}
		index++;
	}
	return (EXIT_SUCCESS);
}
