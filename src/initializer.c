/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:33:59 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/11 20:05:25 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->cmds = NULL;
	shell->num_cmds = 0;
	shell->envp = envp;
	shell->qts.q_marker_str = NULL;
	shell->qts.str = NULL;
}

void	initialize_cmds(t_shell *shell)
{
	int	index;

	index = 0;
	while (index < shell->num_cmds)
	{
		shell->cmds[index].args = NULL;
		shell->cmds[index].cmd_path = NULL;
		shell->cmds[index].envp = shell->envp;
		shell->cmds[index].error = 0;
		shell->cmds[index].line = NULL;
		shell->cmds[index].q_type = NULL;
		shell->cmds[index].access_status = 0;
		shell->cmds[index].num_splits = 0;
		shell->cmds[index].ind_arg = 0;
		shell->cmds[index].ind_start = 0;
		shell->cmds[index].len = 0;
		index++;
	}
}

void	nullify_array(char	**arr, int size)
{
	int	index;

	index = 0;
	if (arr == NULL)
		return ;
	while (index < size)
	{
		*arr = NULL;
		index++;
	}
}
