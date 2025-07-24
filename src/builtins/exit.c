/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:15:44 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/24 17:09:33 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_number(char *str);

void	bin_exit(t_shell *shell, char **args)
{
	int	index;

	index = 0;
	while (args[index])
		index++;
	ft_putendl_fd("exit", 1);
	if (index > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments",
			STDERR_FILENO);
		shell->last_exit = EXIT_FAILURE;
		return ;
	}
	else if (index == 2)
	{
		if (is_number(args[1]) == 0)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			crit_except(shell, ER_SYNTAX);
		}
		shell->last_exit = (unsigned char)ft_atoi(args[1]);
	}
	main_clean_exit(shell);
}

static int	is_number(char *str)
{
	int	index;

	index = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		index++;
	while (ft_isdigit(str[index]))
		index++;
	if (str[index] == '\0')
		return (1);
	return (0);
}
