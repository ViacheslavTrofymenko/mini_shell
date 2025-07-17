/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:17:37 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/17 16:27:30 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_in_str(t_shell *shell, char **str, int len, int start);

void	expand_dollars(t_shell *shell, char **str, char *q_str)
{
	int		index;

	index = 0;
	while (*str[index])
	{
		if (*str[index] == Q_DOLLAR && q_str[index] != Q_SINGLE)
			replace_variable(shell, str, q_str, index);
		index++;
	}
}

void	replace_variable(t_shell *shell, char **str, char *q_str, int start)
{
	int		index;
	int		len;

	index = start + 1;
	len = 1;
	if (ft_isdigit(*str[index]) == 0)
	{
		while (ft_isalnum_(*str[index]) && q_str[index] == q_str[start])
		{
			index++;
			len++;
		}
	}
	else
		len = 2;
	insert_in_str(shell, str, len, start);
}

static void	insert_in_str(t_shell *shell, char **str, int len, int start)
{
	char	*find;
	char	*temp;
	int		len_ins;
	int		len_str;

	find = get_var_value(shell->envp, &(*str[start + 1]), shell->size_env, len);
	if (find == NULL)
		find = get_var_value(shell->vars, &(*str[start + 1]),
				shell->size_vars, len);
	if (find == NULL)
		len_ins = 0;
	else
		len_ins = ft_strlen(find);
	len_str = ft_strlen(*str);
	temp = malloc((len_str - (len + 1) + len_ins + 1) * sizeof(char));
	if (temp == NULL)
		crit_except(shell, ER_MALLOC);
	ft_strlcpy(temp, *str, start + 2);
	ft_strlcpy(&temp[start], find, len_ins + 1);
	ft_strlcpy(&(temp[start + len_ins - 1]), &(*str[start + len + 1]),
		len_str - start - len + 1);
	free(*str);
	*str = temp;
}
