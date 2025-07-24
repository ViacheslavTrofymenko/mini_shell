/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:26:55 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/24 18:27:59 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_perror_custom(char *str, int saved_errno)
{
	if (!str || str[0] == '\0')
		str = "unknown";
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(saved_errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	ft_error(char *str, int saved_errno)
{
	// printf("PERRR %d\n", saved_errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (saved_errno == ENOENT)
	{
		if (ft_strchr(str, '/'))
			ft_putstr_fd("No such file or directory\n", 2);
		else
			ft_putstr_fd("command not found\n", 2);
		return (ER_CMD_NOT_FOUND);
	}
	if (saved_errno == EACCES)
	{
		if (opendir(str) != 0)
			ft_putstr_fd("Is a directory\n", 2);
		else
			ft_putstr_fd("Permission denied\n", 2);
		return (ER_CMD_NOT_EXEC);
	}
	return (1);
}
