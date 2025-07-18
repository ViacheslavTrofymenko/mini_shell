/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:37:57 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/14 16:09:47 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int		diff;

	diff = 0;
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			diff = (unsigned char)*s1 - (unsigned char)*s2;
			return (diff);
		}
		s1++;
		s2++;
	}
	if (*s1 != *s2)
	{
		diff = (unsigned char)*s1 - (unsigned char)*s2;
		return (diff);
	}
	return (diff);
}

int	ft_isalnum_(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (8);
	if (('0' <= c && c <= '9'))
		return (8);
	if (c == '_')
		return (8);
	return (0);
}

int	ft_is_space(char c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

int	ft_is_mol(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
int	ft_is_spec(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}
void	ft_strcpy(char *dest, char *src)
{
	int	index;

	index = 0;	
	if (dest == NULL || src == NULL)
		return ;
	while (src[index] && dest[index])
	{
		dest[index] = src[index];
		index++;
	}
	if (dest[index])
		dest[index] = src[index];
}

char	*safe_strdup(t_shell *shell, char **str)
{
	int		len;
	char	*temp;

	if (str == NULL || *str == NULL)
		return (NULL);
	len = ft_strlen(*str);
	temp = malloc((len + 1) * sizeof(char));
	if (temp == NULL)
		crit_except(shell, ER_MALLOC);
	ft_strlcpy(temp, *str, len + 1);
	free(*str);
	*str = NULL;
	return (temp);
}