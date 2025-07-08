/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:33:59 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/08 19:38:00 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->cmds = NULL;
	shell->envp = envp;
	shell->qts.q_marker_prt = NULL;
	shell->qts.q_marker_str = NULL;
	shell->qts.result = NULL;
	shell->qts.types = NULL;
	shell->qts.str = NULL;
}
