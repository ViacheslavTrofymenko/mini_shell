/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:09:51 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/04 14:59:50 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	if (argc > 1)
		return (EXIT_FAILURE);
	argv[0] = argv[0];
	envp[0] = envp[0];
	line = readline("minishell: ");
	printf("Line: %s\n", line);
	rl_clear_history();
	free(line);
	return (EXIT_SUCCESS);
}
