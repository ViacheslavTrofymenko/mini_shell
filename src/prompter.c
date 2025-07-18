/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:11:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/18 16:32:03 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cmd_line(t_shell *shell)
{
	char	*line;
	int		len;

	line = readline("minishell: ");
	while (ft_strcmp(line, "exit") != 0)
	{
		add_history(line);
		rl_on_new_line();
		mark_quotes(shell, line);
		len = check_assignment(line, shell->qts.q_marker_str);
		if (len > 0)
			replace_var_in_arr(shell, &(shell->vars), &(shell->qts.str), &(shell->size_vars));
		else
		{
			expand_dollars(shell, &(shell->qts.str), shell->qts.q_marker_str);
			printf("Line: %s|\n", shell->qts.str);
		}
		for (int i=0;i<shell->size_vars; i++)
			printf("%s ", shell->vars[i]);
		printf("\n");
/*		printf("Line: %s\nMark: %s\n", line, shell->qts.q_marker_str);
		create_cmd_vars(shell, line);
		// printf("Number of files:%d\n", shell->cmds[0].num_files);
		// for (int i=0;i<shell->cmds[0].num_files; i++)
		// 	printf("%s ", shell->cmds[0].f_names[i]);
		// printf("\nFile types:%d\n", shell->cmds[0].num_files);
		// for (int i=0;i<shell->cmds[0].num_files; i++)
		// 	printf("%d ", shell->cmds[0].rw_type[i]);
		// printf("\nFile modes:%d\n", shell->cmds[0].num_files);
		// 	for (int i=0;i<shell->cmds[0].num_files; i++)
		// 		printf("%d ", shell->cmds[0].f_mode[i]);
		// printf("\nNumber of outputs:%d\n", shell->cmds[0].num_output);
		// printf("\nNumber of args: %d\n", shell->cmds[0].num_args);
		// for (int i=0;i<shell->cmds[0].num_args; i++)
		// 	printf("%s ", shell->cmds[0].args[i]);
		// printf("\n");
		execute_cmds(shell);
		// crit_except(shell, 0);
		line = readline("minishell: ");
	}
	clean_double_arr(shell->vars, shell->size_vars);
	clean_double_arr(shell->envp, shell->size_env);
	free(line);
}
