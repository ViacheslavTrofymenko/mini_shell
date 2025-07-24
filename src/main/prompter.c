/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:11:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/23 19:02:23 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	schedule_jobs(t_shell *shell);
static char	*make_fancy_prompt(t_shell *shell);
static char	*get_username(t_shell *shell);
static void	add_addr(t_shell *shell, char **temp1, char **temp2, char *find);

void	get_cmd_line(t_shell *shell)
{
	shell->prompt = make_fancy_prompt(shell);
	interactive_signal_handler();
	sigterm_handler();
	shell->cmd_line = readline(shell->prompt);
	while (1)
	{		
		noninteractive_signal_handler();
		handle_ctrl_d(shell);
		if (ft_strlen(shell->cmd_line))
		{
			add_history(shell->cmd_line);
			rl_on_new_line();
			mark_quotes(shell, shell->cmd_line);
			create_cmd_vars(shell, shell->cmd_line);
			schedule_jobs(shell);
		}
		crit_except(shell, 0);
		update_error_on_signal(shell);
		shell->prompt = make_fancy_prompt(shell);
		interactive_signal_handler();
		shell->cmd_line = readline(shell->prompt);
		update_error_on_signal(shell);
	}
}

static void	schedule_jobs(t_shell *shell)
{
	if (check_syntax_except(shell))
		return ;
	if (shell->num_cmds == 1 && shell->cmds[0].num_args == 0)
		transform_env(shell, &(shell->cmds[0]));
	execute_cmds(shell);
}

static char	*make_fancy_prompt(t_shell *shell)
{
	char	*find;
	char	*temp1;
	char	*temp2;

	temp2 = get_username(shell);
	find = get_var_value(shell->envp, "HOME", shell->size_env, 4);
	add_addr(shell, &temp1, &temp2, find);
	free(temp2);
	temp2 = safe_strjoin(shell, temp1, C_RESET"$ ");
	free(temp1);
	return (temp2);
}

static char	*get_username(t_shell *shell)
{
	char	*find;
	char	*temp1;
	char	*temp2;

	find = get_var_value(shell->envp, "USER", shell->size_env, 4);
	temp1 = ""C_GRN;
	if (find)
		temp1 = safe_strjoin(shell, temp1, find);
	temp2 = safe_strjoin(shell, temp1, "@");
	if (find)
		free(temp1);
	find = get_var_value(shell->envp, "SESSION_MANAGER", shell->size_env, 15);
	if (find)
	{
		temp1 = malloc ((ft_strlen(temp2) + 7) * sizeof(char));
		if (temp1 == NULL)
			crit_except(shell, ER_MALLOC);
		ft_strlcpy(temp1, temp2, ft_strlen(temp2) + 1);
		ft_strlcat(&(temp1[ft_strlen(temp2) - 1]), &(find[6]), 8);
		free(temp2);
	}
	else
		temp1 = temp2;
	temp2 = safe_strjoin(shell, temp1, C_RESET":"C_BLU);
	return (free(temp1), temp2);
}

static void	add_addr(t_shell *shell, char **temp1, char **temp2, char *find)
{
	int		index;
	char	buffer[BUFFER_SIZE];

	index = 0;
	getcwd(buffer, BUFFER_SIZE);
	while (find && find[index] == buffer[index] && buffer[index])
		index++;
	if (buffer[index])
	{
		if (find)
		{
			*temp1 = *temp2;
			*temp2 = safe_strjoin(shell, *temp2, "~");
			free(*temp1);
		}
		*temp1 = safe_strjoin(shell, *temp2, &(buffer[index]));
	}
	else
	{
		if (find && (int)ft_strlen(find) == index)
			*temp1 = safe_strjoin(shell, *temp2, "~");
		else
			*temp1 = safe_strjoin(shell, *temp2, buffer);
	}
}

