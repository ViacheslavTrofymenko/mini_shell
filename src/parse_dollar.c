/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:17:37 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/18 19:48:02 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*insert_var(t_shell *shell, char **str, int len, int start);
static char	*insert_dummy(char **str, char *find, int len, int start);
void		expand_var(t_shell *shell, char **str, char **q_str, int start);
void		expand_error(t_shell *shell, char **str, char **q_type, int start);

void	expand_dollars(t_shell *shell, char **str, char **q_str)
{
	int		index;

	index = 0;
	while ((*str)[index])
	{
		if ((*str)[index] == Q_DOLLAR && (*q_str)[index] != Q_SINGLE
			&& (*str)[index + 1] == Q_QUEST)
			expand_error(shell, str, q_str, index);
		else if ((*str)[index] == Q_DOLLAR && (*q_str)[index] != Q_SINGLE)
			expand_var(shell, str, q_str, index);
		index++;
	}
	remove_quote_marks(*str, *q_str);
}

void	expand_var(t_shell *shell, char **str, char **q_str, int start)
{
	int		index;
	int		len;
	char	*find;

	index = start + 1;
	len = 1;
	if (ft_isdigit((*str)[index]) == 0)
	{
		while (ft_isalnum_((*str)[index]) && q_str[index] == q_str[start])
		{
			index++;
			len++;
		}
	}
	else
		len = 2;
	find = insert_var(shell, str, len - 1, start);
	find = insert_dummy(q_str, find, len - 1, start);
	if (find == NULL)
		crit_except(shell, ER_MALLOC);
}

static char	*insert_var(t_shell *shell, char **str, int len, int start)
{
	char	*find;
	char	*temp;

	find = get_var_value(shell->envp,
			&((*str)[start + 1]), shell->size_env, len);
	if (find == NULL)
		find = get_var_value(shell->vars, &((*str)[start + 1]),
				shell->size_vars, len);
	temp = insert_str_to_str(str, find, start, len + 1);
	if (temp == NULL)
		crit_except(shell, ER_MALLOC);
	return (find);
}

static char	*insert_dummy(char **str, char *find, int len, int start)
{
	char	*dummy;
	int		index;
	int		len_find;

	index = -1;
	dummy = NULL;
	if (find)
	{
		len_find = ft_strlen(find);
		dummy = malloc ((len_find + 1) * sizeof(char));
		if (dummy == NULL)
			return (NULL);
		while (++index < len_find)
			dummy[index] = Q_SINGLE;
		dummy[index] = '\0';
	}
	find = insert_str_to_str(str, dummy, start, len + 1);
	free(dummy);
	return (*str);
}

void	expand_error(t_shell *shell, char **str, char **q_type, int start)
{
	char	*er_code;
	char	*temp;
	int		len;
	int		index;

	index = -1;
	er_code = ft_itoa(shell->last_exit);
	if (er_code == NULL)
		crit_except(shell, ER_MALLOC);
	len = ft_strlen(er_code);
	temp = insert_str_to_str(str, er_code, start, 2);
	if (temp == NULL)
		crit_except(shell, ER_MALLOC);
	free(er_code);
	temp = malloc((len + 1) * sizeof(char));
	if (temp == NULL)
		crit_except(shell, ER_MALLOC);
	while (++index < len)
		temp[index] = Q_SINGLE;
	temp[index] = '\0';
	er_code = insert_str_to_str(q_type, temp, start, 2);
	if (er_code == NULL)
		crit_except(shell, ER_MALLOC);
	free(temp);
}
