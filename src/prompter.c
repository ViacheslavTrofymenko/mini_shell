/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:11:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/08 19:56:23 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_splits(t_qoutes *qts);

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
		parse_quotes(shell, line);
		printf("Num of splits: %d\n", shell->qts.num_splits);
		print_splits(&(shell->qts));
		printf("Line: %s\nMark: %s\n", line, shell->qts.q_marker_str);
		find_pipes(shell, line);
		printf("First pipe: %s\n", ((t_cmd *)shell->cmds->content)->line);
		free(line);
		crit_except(shell, 0);
		line = readline("minishell: ");
	}
	free(line);
}

static void	print_splits(t_qoutes *qts)
{
	int	index;

	index = 0;
	while (index < qts->num_splits)
	{
		printf("%s, type = \"%c\"\n", qts->result[index], qts->types[index]);
		index++;
	}
}

