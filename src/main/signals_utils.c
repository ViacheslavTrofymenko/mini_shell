/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:47:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/23 18:53:21 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_error_on_signal(t_shell *shell)
{
	if (g_last_signal != 0)
	{
		shell->last_exit = SIG_SHIFT + g_last_signal;
		g_last_signal = 0;
	}
}
