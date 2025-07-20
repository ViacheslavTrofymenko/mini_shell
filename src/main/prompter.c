/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:11:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/18 19:52:16 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	schedule_jobs(t_shell *shell);
static char	*make_fancy_prompt(t_shell *shell);

void	get_cmd_line(t_shell *shell)
{
	shell->prompt = make_fancy_prompt(shell);
	shell->cmd_line = readline(shell->prompt);
	while (1/*ft_strcmp(line, "exit") != 0*/)
	{
		add_history(shell->cmd_line);
		rl_on_new_line();
		mark_quotes(shell, shell->cmd_line);
		create_cmd_vars(shell, shell->cmd_line);
		if (shell->cmds[0].num_args > 0 && ft_strcmp(shell->cmds[0].args[0], "export") == 0)
			bin_export(shell, shell->cmds[0].args);
		else if (shell->cmds[0].num_args > 0 && ft_strcmp(shell->cmds[0].args[0], "unset") == 0)
			bin_unset(shell, shell->cmds[0].args);
		else if (shell->cmds[0].num_args > 0 && ft_strcmp(shell->cmds[0].args[0], "exit") == 0)
			bin_exit(shell, shell->cmds[0].args);
		else
			schedule_jobs(shell);
		crit_except(shell, 0);
		shell->prompt = make_fancy_prompt(shell);
		shell->cmd_line = readline(shell->prompt);
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
	char	buffer[BUFFER_SIZE];

	find = get_var_value(shell->envp, "USER", shell->size_env, 4);
	temp1 = C_GRN;
	if (find)
		temp1 = safe_strjoin(shell, C_GRN, find);
	temp2 = safe_strjoin(shell, temp1, "@");
	if (find)
		free(temp1);
	find = get_var_value(shell->envp, "NAME", shell->size_env, 4);
	if (find)
		temp1 = safe_strjoin(shell, temp2, find);
	if (find)
		free(temp2);
	temp2 = safe_strjoin(shell, temp1, C_RESET":"C_BLU);
	if (find)
		free(temp1);
	getcwd(buffer, BUFFER_SIZE);
	temp1 = safe_strjoin(shell, temp2, buffer);
	free(temp2);
	temp2 = safe_strjoin(shell, temp1, C_RESET"$ ");
	return (free(temp1), temp2);
}

/*	DEBUG FUNCTIONS
	printf("Line: %s\nMark: %s\n", line, shell->qts.q_marker_str);
	printf("\nNumber of files:%d\n", shell->cmds[0].num_files);
	for (int i=0;i<shell->cmds[0].num_files; i++)
		printf("%s ", shell->cmds[0].f_names[i]);
	printf("\nFile types:%d\n", shell->cmds[0].num_files);
	for (int i=0;i<shell->cmds[0].num_files; i++)
		printf("%d ", shell->cmds[0].rw_type[i]);
	printf("\nFile modes:%d\n", shell->cmds[0].num_files);
		for (int i=0;i<shell->cmds[0].num_files; i++)
			printf("%d ", shell->cmds[0].f_mode[i]);
	printf("\nNumber of outputs:%d\n", shell->cmds[0].num_output);
	printf("\nNumber of args: %d\n", shell->cmds[0].num_args);
	for (int i=0;i<shell->cmds[0].num_args; i++)
		printf("%s ", shell->cmds[0].args[i]);
	printf("\nNumber of assign: %d\n", shell->cmds[0].num_assign);
	for (int i=0;i<shell->cmds[0].num_assign; i++)
		printf("%s ", shell->cmds[0].assign[i]);		
	printf("\nCurrent vars: ");
	for (int i=0;i<shell->size_vars; i++)
		printf("%s ", shell->vars[i]);
	printf("\n");*/

