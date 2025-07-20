/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics_advanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:31:23 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/19 18:31:23 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*safe_strdup(t_shell *shell, char *str)
{
	int		len;
	char	*temp;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	temp = malloc((len + 1) * sizeof(char));
	if (temp == NULL)
		crit_except(shell, ER_MALLOC);
	ft_strlcpy(temp, str, len + 1);
	return (temp);
}

char	**duplicate_arr(t_shell *shell, char **arr, int *new_size)
{
	int		index;
	char	**result;

	index = 0;
	if (arr == NULL)
		return (NULL);
	while (arr[index] != NULL)
		index++;
	result = malloc ((index + 1) * sizeof(char *));
	if (result == NULL)
		crit_except(shell, ER_MALLOC);
	nullify_array(result, index + 1);
	result[index] = NULL;
	*new_size = index + 1;
	while (--index >= 0)
	{
		result[index] = ft_strdup(arr[index]);
		if (result[index] == NULL)
		{
			clean_double_arr(result, *new_size);
			crit_except(shell, ER_MALLOC);
		}
	}
	return (result);
}

char	*safe_strjoin(t_shell *shell, char *s1, char *s2)
{
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	result = ft_strjoin(s1, s2);
	if (result == NULL)
		crit_except(shell, ER_MALLOC);
	return (result);
}

void	safe_free(char **s)
{
	if (s != NULL && *s != NULL)
	{
		free(*s);
		*s = NULL;
	}
}

void	nullify_array(char	**arr, int size)
{
	int	index;

	index = 0;
	if (arr == NULL)
		return ;
	while (index < size)
	{
		arr[index] = NULL;
		index++;
	}
}
