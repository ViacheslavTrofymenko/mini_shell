/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:08:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/08 19:54:33 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_node(void *arg);

void	crit_except(t_shell *data, int error_code)
{
	int	index;

	index = 0;
	if (data->qts.result != NULL)
	{
		while (index < data->qts.ind_line)
		{
			free(data->qts.result[index]);
			index++;
		}
		free(data->qts.result);
		free(data->qts.types);
		free(data->qts.q_marker_prt);
		free(data->qts.q_marker_str);
	}
	ft_lstclear(&(data->cmds), delete_node);
	data->cmds = NULL;
	if (error_code != 0)
		exit (error_code);
}

static void	delete_node(void *arg)
{
	t_cmd	*cmd;

	cmd = arg;
	if (cmd == NULL)
		return ;
	if (cmd->line != NULL)
		free(cmd->line);
	if (cmd->q_type != NULL)
		free(cmd->q_type);
	free(cmd);
}
