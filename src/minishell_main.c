/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:09:51 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/12 17:43:08 by ikulik           ###   ########.fr       */
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


