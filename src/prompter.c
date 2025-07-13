/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:11:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/12 18:33:46 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void	print_cmds(t_shell *shell);

void	get_cmd_line(t_shell *shell)
{
	char	*line;

	line = readline("minishell: ");
	add_history(line);
	while (ft_strcmp(line, "exit") != 0)
	{
		printf("Line read: %s\n", line);
		add_history(line);
		rl_on_new_line();
		mark_quotes(shell, line);
		printf("Line: %s\nMark: %s\n", line, shell->qts.q_marker_str);
		create_cmd_vars(shell, line);
		printf("Num of cmds:%d\n", shell->num_cmds);
		printf("Number of inputs:%d\n", shell->cmds[0].num_input);
		for (int i=0;i<shell->cmds[0].num_input; i++)
			printf("%s ", shell->cmds[0].in_names[i]);
		printf("\nNumber of outputs:%d\n", shell->cmds[0].num_output);
		for (int i=0;i<shell->cmds[0].num_output; i++)
			printf("%s ", shell->cmds[0].out_names[i]);
		printf("\nNumber of args: %d\n", shell->cmds[0].num_args);
		for (int i=0;i<shell->cmds[0].num_args; i++)
			printf("%s ", shell->cmds[0].args[i]);
		printf("\n");
		crit_except(shell, 0);
		line = readline("minishell: ");
	}
	free(line);
}

/*static void	print_cmds(t_shell *shell)
{
	int	index;

	index = 0;
	if (shell->cmds == NULL)
		return ;
	while (index < shell->num_cmds)
	{
		printf("Cmd %d: %s\nQts_l: %s\n", index, shell->cmds[index].line, shell->cmds[index].q_type);
		index++;
	}
}*/

