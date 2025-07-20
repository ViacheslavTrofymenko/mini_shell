/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:17:37 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/18 18:12:28 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*insert_str_to_str(char **str, char *ins, int start, int len)
{
	char	*temp;
	int		len_ins;
	int		len_str;

	if (ins == NULL)
		len_ins = 0;
	else
		len_ins = ft_strlen(ins);
	len_str = ft_strlen(*str);
	temp = malloc((len_str - len + len_ins + 1) * sizeof(char));
	if (temp == NULL)
		return (NULL);
	ft_strlcpy(temp, *str, start + 1);
	if (ins)
		ft_strlcpy(&temp[start], ins, len_ins + 1);
	ft_strlcpy(&(temp[start + len_ins]), &((*str)[start + len]),
		len_str - start - (len - 1));
	free(*str);
	*str = temp;
	return (*str);
}

int	check_assignment(char *arg, char *q_type)
{
	int	index;

	index = 0;
	if (arg == NULL)
		return (0);
	if (ft_isdigit(arg[0]))
		return (0);
	while (ft_isalnum_(arg[index]))
		index++;
	if (q_type != NULL)
	{
		if (arg[index] == '=' && q_type[index] == Q_NORMAL && index > 0)
			return (index);
	}
	else if (arg[index] == '=')
			return (index);
	return (0);
}
