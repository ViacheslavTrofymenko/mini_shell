/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:11:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/04 16:43:22 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	get_cmd_line(void)
{
	char	*line;

	line = readline("minishell: ");
	while (ft_strncmp(line, "exit") != 0)
	{
		printf("Line read: %s\n", line);
		rl_on_new_line();
		line = readline("minishell: ");
	}
}
