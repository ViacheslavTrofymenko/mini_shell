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

void	get_cmd_line(t_shell *shell)
{
	char	*line;

	line = readline("minishell: ");
	while (ft_strcmp(line, "exit") != 0)
	{
		add_history(line);
		rl_on_new_line();
		mark_quotes(shell, line);
		create_cmd_vars(shell, line);
		schedule_jobs(shell);
		crit_except(shell, 0);
		line = readline("minishell: ");
	}
	clean_double_arr(shell->vars, shell->size_vars);
	clean_double_arr(shell->envp, shell->size_env);
	free(line);
}

static void	schedule_jobs(t_shell *shell)
{
	if (check_syntax_except(shell))
		return ;
	if (shell->num_cmds == 1 && shell->cmds[0].num_args == 0)
		transform_env(shell, &(shell->cmds[0]));
	execute_cmds(shell);
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

