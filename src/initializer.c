/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:33:59 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/17 18:13:45 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_start_env(t_shell *shell, char **envp);

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->cmds = NULL;
	shell->num_cmds = 0;
	shell->envp = NULL;
	shell->qts.q_marker_str = NULL;
	shell->qts.str = NULL;
	create_start_env(shell, envp);
	initialize_cmd_p(&(shell->cmd_p));
}

void	initialize_cmd_p(t_cmd_p *cmd)
{
	cmd->args = NULL;
	cmd->line = NULL;
	cmd->q_type = NULL;
	cmd->f_names = NULL;
	cmd->f_mode = NULL;
	cmd->rw_type = NULL;
	cmd->splits = NULL;
	cmd->split_qs = NULL;
	cmd->split_io = NULL;
	cmd->num_input = 0;
	cmd->num_output = 0;
	cmd->num_splits = 0;
	cmd->num_args = 0;
	cmd->ind_arg = 0;
	cmd->ind_start = 0;
	cmd->len = 0;
	cmd->er_synt_char = NULL;
	cmd->error = 0;
}

void	initialize_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->f_names = NULL;
	cmd->f_mode = NULL;
	cmd->rw_type = NULL;
	cmd->num_input = 0;
	cmd->num_output = 0;
	cmd->er_synt_char = '\0';
	cmd->error = 0;
}

void	nullify_array(char	**arr, int size)
{
	int	index;

	index = 0;
	if (arr == NULL)
		return ;
	while (index < size)
	{
		arr[index] = NULL;
		index++;
	}
}

static void	create_start_env(t_shell *shell, char **envp)
{
	int	size_env;

	size_env = 0;
	shell->vars = NULL;
	shell->size_vars = 1;
	shell->vars = malloc (sizeof(char *));
	if (shell->vars == NULL)
		crit_except(shell, ER_MALLOC);
	shell->vars[0] = NULL;
	while(envp[size_env])
		size_env++;
	size_env++;
	shell->envp = malloc(size_env * sizeof(char *));
	if (shell->envp == NULL)
		crit_except(shell, ER_MALLOC);
	shell->size_env = size_env;
	nullify_array(shell->envp, size_env);
	size_env--;
	while (--size_env >= 0)
	{
		shell->envp[size_env] = ft_strdup(envp[size_env]);
		if (shell->envp[size_env] == NULL)
			crit_except(shell, ER_MALLOC);
	}
}
