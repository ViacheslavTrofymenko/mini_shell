/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:33:06 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/17 16:29:49 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
