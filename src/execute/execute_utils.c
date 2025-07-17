/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:39:54 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/17 14:32:38 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(int num, char *str)
{
	if (num == 1)
		perror(str);
	if (num == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (1);
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

char	*ft_get_path_command(char **cmd, char **envp)
{
	int		i;
	char	**path_list;
	char	*path_command;

	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		return (NULL);
	if (ft_strchr(cmd[0], '/'))
		if (access(cmd[0], X_OK) == 0)
			return (ft_strdup(cmd[0]));
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			path_list = ft_split(envp[i] + 5, ':');
			path_command = ft_check_command(path_list, cmd[0]);
			ft_free_str_array(path_list);
			return (path_command);
		}
	}
	return (NULL);
}
