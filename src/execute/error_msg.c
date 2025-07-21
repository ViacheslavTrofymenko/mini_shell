/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:26:55 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/21 12:41:01 by vtrofyme         ###   ########.fr       */
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
		if (saved_errno == EACCES)
		return (ER_CMD_NOT_EXEC);
	else if (saved_errno == ENOENT)
		return (ER_CMD_NOT_FOUND);
	else if (saved_errno == ENOTDIR)
		return (ER_CMD_NOT_EXEC);
	else if (saved_errno == EISDIR)
		return (ER_CMD_NOT_EXEC);
	else if (saved_errno == ENOEXEC)
		return (ER_CMD_NOT_EXEC);
	else if (saved_errno == E2BIG)
		return (ER_CMD_NOT_EXEC);
	else if (saved_errno == ENOMEM)
		return (1);
	else if (saved_errno == EFAULT)
		return (1);
	else
		return (1);
}

int	ft_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (ER_CMD_NOT_FOUND);
}
