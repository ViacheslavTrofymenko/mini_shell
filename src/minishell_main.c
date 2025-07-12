/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:33:06 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/12 22:15:12 by vtrofyme         ###   ########.fr       */
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
	printf("compare: %d\n", ft_strncmp("<avc", "<", 1));
	get_cmd_line(&shell);
	rl_clear_history();
	return (EXIT_SUCCESS);
}


