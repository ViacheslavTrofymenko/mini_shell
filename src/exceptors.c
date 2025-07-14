/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:43:40 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/13 17:43:40 by ikulik           ###   ########.fr       */
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
	clean_cmd_p(&(data->cmd_p), M_TOTAL);
	clean_cmds(data);
	if (error_code != 0)
		exit (error_code);
}