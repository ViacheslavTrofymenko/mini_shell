/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:50:57 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/23 16:46:16 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_directory(t_shell *shell, char *path, char *oldpwd);
static void	update_env_var(t_shell *shell, char *key, char *value);

void	bin_cd(t_shell *shell, char **args)
{
	char	cwd[1024];
	char	*oldpwd;

	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->last_exit = 1;
		return ;
	}
	if (!args[1])
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		shell->last_exit = 1;
		return ;
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_perror_custom("cd", errno);
		shell->last_exit = 1;
		return ;
	}
	oldpwd = safe_strdup(shell, cwd);
	change_directory(shell, args[1], oldpwd);
	free(oldpwd);
}

static int	change_directory(t_shell *shell, char *path, char *oldpwd)
{
	char	cwd[1024];

	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_perror_custom(path, errno);
		shell->last_exit = 1;
		return (1);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_perror_custom("cd", errno);
		shell->last_exit = 1;
		return (1);
	}
	update_env_var(shell, "OLDPWD", oldpwd);
	update_env_var(shell, "PWD", cwd);
	shell->last_exit = 0;
	return (0);
}

static void	update_env_var(t_shell *shell, char *key, char *value)
{
	char	*full_var;
	char	*temp;

	temp = safe_strjoin(shell, key, "=");
	full_var = safe_strjoin(shell, temp, value);
	free(temp);
	replace_var_in_arr(shell, &(shell->envp), full_var, &(shell->size_env));
	free(full_var);
}
