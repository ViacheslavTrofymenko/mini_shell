/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:02:22 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/17 18:53:19 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_one_slot(t_shell *shell, char ***arr, int *size);

int	is_var_name(char *str)
{
	int	len;
	
	len = 0;
	if (str == NULL)
		return (0);
	if (ft_isdigit(str[0]))
		return (0);
	while (ft_isalnum_(str[len]))
		len++;
	if (str[len] == '\0')
		return (len);
	return (0);
}

int	find_var_index(char **arr, char *var, int size, int len)
{
	int	index;

	index = 0;
	if (arr == NULL)
		return (V_NFOUND);
	while (index < size - 1)
	{
		if (ft_strncmp(arr[index], var, len) == 0)
		{
			if (arr[index][len] == '=')
				return (index);
		}
		index++;
	}
	return (V_NFOUND);
}

void	replace_var_in_arr(t_shell *shell, char ***arr, char *var, int *size)
{
	int	index;
	int	len;

	index = 0;
	len = 0;
	while (var[len] && var[len] != '=')
		len++;
	if (var[len] != '=')
		return ;
	index = find_var_index(*arr, var, *size, len);
	if (index >= 0)
	{
		if (var != (*arr)[index])
		{
			free((*arr)[index]);
			(*arr)[index] = safe_strdup(shell, var);
		}
	}
	else
	{
		add_one_slot(shell, arr, size);
		(*arr)[*size - 2] = safe_strdup(shell, var);
	}
}

static void	add_one_slot(t_shell *shell, char ***arr, int *size)
{
	char	**temp;
	int		index;

	index = 0;
	temp = (char **)malloc((*size + 1) * sizeof(char *));
	if (temp == NULL)
		crit_except(shell, ER_MALLOC);
	while (index < *size - 1)
	{
		temp[index] = (*arr)[index];
		index++;
	}
	temp[*size] = NULL;
	free(*arr);
	*arr = temp;
	(*size)++;
}


char	*get_var_value(char **arr, char *var, int size, int len)
{
	int	ind_find;
	int	index;

	index = 0;
	ind_find = find_var_index(arr, var, size, len);
	if (ind_find == V_NFOUND)
		return (NULL);
	while (arr[ind_find][index] && arr[ind_find][index] != '=')
		index++;
	return (&(arr[ind_find][index + 1]));
}
