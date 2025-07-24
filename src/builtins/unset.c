/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:58:14 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/24 18:38:32 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bin_unset(t_shell *shell, char **args)
{
	int	index;
	int	len;

	index = 1;
	while (args[index])
	{
		len = is_var_name(args[index]);
		if (len > 0)
		{
			take_out_var(shell->envp, args[index], &(shell->size_env), len);
			take_out_var(shell->vars, args[index], &(shell->size_vars), len);
		}
		else
			var_name_error(shell, "unset", args[index]);
		index++;
	}
}

void	take_out_var(char **arr, char *var, int *size, int len)
{
	int	index;

	index = find_var_index(arr, var, *size, len);
	if (index == V_NFOUND)
		return ;
	free(arr[index]);
	while (index < *size - 1)
	{
		arr[index] = arr[index + 1];
		index++;
	}
	(*size)--;
}
