/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:33:59 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/23 19:46:02 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_start_env(t_shell *shell, char **envp);
static void	set_shell_vars(t_shell *shell);

void	initialize_shell(t_shell *shell, char **envp)
{
	shell->cmds = NULL;
	shell->envp = NULL;
	shell->qts.q_marker_str = NULL;
	shell->qts.str = NULL;
	shell->prompt = NULL;
	shell->num_cmds = 0;
	shell->last_exit = 0;
	g_last_signal = 0;
	create_start_env(shell, envp);
	ft_bzero(&(shell->cmd_p), sizeof(t_cmd_p));
	//initialize_cmd_p(&(shell->cmd_p));
	set_shell_vars(shell);
}

/*void	initialize_cmd_p(t_cmd_p *cmd)
{
	ft_bzero(cmd, sizeof(t_cmd_p));
	cmd->args = NULL;
	cmd->line = NULL;
	cmd->q_type = NULL;
	cmd->f_names = NULL;
	cmd->f_mode = NULL;
	cmd->rw_type = NULL;
	cmd->splits = NULL;
	cmd->split_qs = NULL;
	cmd->split_io = NULL;
	cmd->assign = NULL;
	cmd->num_input = 0;
	cmd->num_output = 0;
	cmd->num_splits = 0;
	cmd->num_args = 0;
	cmd->num_assign = 0;
	cmd->ind_arg = 0;
	cmd->ind_start = 0;
	cmd->len = 0;
	cmd->er_synt_char = NULL;
	cmd->error = 0;
}*/

/* void	initialize_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->assign = NULL;
	cmd->f_names = NULL;
	cmd->f_mode = NULL;
	cmd->rw_type = NULL;
	cmd->num_input = 0;
	cmd->num_output = 0;
	cmd->er_synt_char = '\0';
	cmd->error = 0;
} */

static void	create_start_env(t_shell *shell, char **envp)
{
	shell->vars = NULL;
	shell->size_vars = 1;
	shell->vars = malloc (sizeof(char *));
	if (shell->vars == NULL)
		crit_except(shell, ER_MALLOC);
	shell->vars[0] = NULL;
	shell->envp = duplicate_arr(shell, envp, &(shell->size_env));
}

static void	set_shell_vars(t_shell *shell)
{
	char	*find;
	char	*temp1;
	char	*temp2;
	int		val;

	find = get_var_value(shell->envp, "SHLVL", shell->size_env, 5);
	val = 1;
	if (find)
		val = ft_atoi(find) + 1;
	temp1 = ft_itoa(val);
	if (temp1 == NULL)
		crit_except(shell, ER_MALLOC);
	temp2 = ft_strjoin("SHLVL=", temp1);
	free(temp1);
	if (temp2 == NULL)
		crit_except(shell, ER_MALLOC);
	replace_var_in_arr(shell, &(shell->envp), temp2, &(shell->size_env));
	//replace_var_in_arr(shell, &(shell->envp),
	//	"SHELL=minishell", &(shell->size_env));
	free(temp2);
}
