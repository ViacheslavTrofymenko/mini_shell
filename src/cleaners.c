/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:08:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/07 16:51:54 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	}
	if (error_code != 0)
		exit (error_code);
}
