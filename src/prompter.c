/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:11:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/07 16:54:03 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_splits(t_qoutes *qts);

void	get_cmd_line(void)
{
	char	*line;
	t_shell	shell;

	line = readline("minishell: ");
	add_history(line);
	while (ft_strcmp(line, "exit") != 0)
	{
		printf("Line read: %s\n", line);
		add_history(line);
		rl_on_new_line();
		parse_quotes(&shell, line);
		printf("Num of splits: %d\n", shell.qts.num_splits);
		print_splits(&(shell.qts));
		free(line);
		crit_except(&shell, 0);
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

