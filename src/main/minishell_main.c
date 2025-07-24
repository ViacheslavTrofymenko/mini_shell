/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:33:06 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/24 18:28:06 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_signal;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc > 1)
		return (EXIT_FAILURE);
	argv[0] = argv[0];
	initialize_shell(&shell, envp);
	get_cmd_line(&shell);
	return (EXIT_SUCCESS);
}
