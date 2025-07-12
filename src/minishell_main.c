/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:09:51 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/12 09:10:39 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *myfunc(void)
{
	char *line;
line = readline("minishell: ");
	return (line);

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc > 1)
		return (EXIT_FAILURE);
	argv[0] = argv[0];
	initialize_shell(&shell, envp);
	get_cmd_line(&shell);
	rl_clear_history();
	return (EXIT_SUCCESS);
}


