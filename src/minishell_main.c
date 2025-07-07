/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:33:06 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/05 09:27:48 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *myfunc(void)
{
	char *line;
line = readline("minishell: ");
	return (line);

}
int	main(int argc, char **argv)
{
	char	*line;

	if(argc == 2)
	{
		argv[1] = argv[3];
	}
	line = myfunc();
	free(line);
	return (0);
}
