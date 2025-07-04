/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:33:06 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/04 14:38:24 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*line;

	if(argc == 2)
	{
		argv[1] = argv[3];
	}
	line = readline("minishell: ");
	free(line);
	return (0);
}
