/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:25:35 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/22 22:22:25 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char **args)
{
	if (args == NULL)
		return (0);
	if (ft_strcmp(args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(args[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(args[0], "cd") == 0)
		return (1);
	return (0);
}

void	run_builtin(t_shell *shell, char **args)
{
	if (args == NULL)
		return ;
	if (ft_strcmp(args[0], "export") == 0)
		bin_export(shell, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		bin_unset(shell, args);
	else if (ft_strcmp(args[0], "exit") == 0)
		bin_exit(shell, args);
	else if (ft_strcmp(args[0], "echo") == 0)
		bin_echo(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		bin_pwd();
	else if (ft_strcmp(args[0], "cd") == 0)
		bin_cd(shell, args);
}

int	is_builtin_parent_only(char *cmd)
{
	if (!cmd)
		return (0);
	return (
		ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0
	);
}
