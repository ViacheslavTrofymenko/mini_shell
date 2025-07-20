/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:48:08 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/19 19:48:08 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_var(t_shell *shell, char *var, int mode);
static void	check_for_export(t_shell *shell, char *var);
static void	print_sorted_env(t_shell *shell);

void	bin_export(t_shell *shell, char **args)
{
	int	index;

	index = 1;
	if (args == NULL)
		return ;
	if (args[1] == NULL)
		print_sorted_env(shell);
	while (args[index])
	{
		check_for_export(shell, args[index]);
		index++;
	}
}

static void	print_sorted_env(t_shell *shell)
{
	char	*temp;
	char	**temp_arr;
	int		size;
	int		i;
	int		j;

	temp_arr = duplicate_arr(shell, shell->envp, &size);
	i = -1;
	while (++i < size - 2)
	{
		j = i;
		while (++j < size - 1)
		{
			if (ft_strcmp(temp_arr[i], temp_arr[j]) > 0)
			{
				temp = temp_arr[i];
				temp_arr[i] = temp_arr[j];
				temp_arr[j] = temp;
			}
		}
	}
	i = -1;
	while (++i < size - 1)
		ft_putendl_fd(temp_arr[i], STDOUT_FILENO);
	clean_double_arr(temp_arr, size);
}
static void	check_for_export(t_shell *shell, char *var)
{
	int	find;
	int	len;	
	
	len = is_var_name(var);
	find = check_assignment(var, NULL);
	if (len > 0)
	{
		find = find_var_index(shell->vars, var,
			shell->size_vars, len);
		if (find >= 0)
			export_var(shell, shell->vars[find], M_AS_IS);
		else
			export_var(shell, var, M_ADDEQUAL);
	}
	else if (find > 0)
		export_var(shell, var, M_AS_IS);
	else
		var_name_error(shell, "export", var);
}
static void	export_var(t_shell *shell, char *var, int mode)
{
	char	*temp;
	int		len;

	temp = var;
	if (mode == M_ADDEQUAL)
	{
		len = ft_strlen(var);
		temp = malloc ((len + 2) * sizeof(char));
		if (temp == NULL)
			crit_except(shell, ER_MALLOC);
		ft_strlcpy(temp, var, len + 1);
		temp[len] = '=';
		temp[len + 1] = '\0';
	}
	replace_var_in_arr(shell, &(shell->envp), temp, &(shell->size_env));
	replace_var_in_arr(shell, &(shell->vars), temp, &(shell->size_vars));
}

void	var_name_error(t_shell *shell, char *function, char *var)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(function, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	shell->last_exit = EXIT_FAILURE;
}
