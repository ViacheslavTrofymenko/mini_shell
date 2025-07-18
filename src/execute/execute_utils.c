/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:39:54 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/18 14:56:26 by vtrofyme         ###   ########.fr       */
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

char	*ft_check_command(char **path_list, char *cmd)
{
	int		i;
	char	*path_fin;
	char	*path_mid;

	i = 0;
	while (path_list[i])
	{
		path_mid = ft_strjoin(path_list[i], "/");
		path_fin = ft_strjoin(path_mid, cmd);
		free(path_mid);
		if (access(path_fin, X_OK) == 0)
			return (path_fin);
		free(path_fin);
		i++;
	}
	return (NULL);
}

void	ft_free_str_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*ft_get_path_command(t_shell *shell, int i)
{
	int		j;
	char	**path_list;
	char	*path_command;
	t_cmd	*cmd;

	cmd = &shell->cmds[i];
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], X_OK) == -1)
			crit_except(shell, ft_perror_custom(cmd->args[0], errno));
		else
			return (ft_strdup(cmd->args[0]));
	}
	j = -1;
	while (cmd->envp && cmd->envp[++j])
	{
		if (!ft_strncmp("PATH=", cmd->envp[j], 5))
		{
			path_list = ft_split(cmd->envp[j] + 5, ':');
			path_command = ft_check_command(path_list, cmd->args[0]);
			ft_free_str_array(path_list);
			return (path_command);
		}
	}
	return (NULL);
}
