/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 01:46:21 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/04/12 01:46:24 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_size_of_mem(char *s, char c)
{
	size_t	count;
	size_t	in_string;

	count = 0;
	in_string = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			in_string = 0;
		else
		{
			if (!in_string)
			{
				in_string = 1;
				count++;
			}
		}
		s++;
	}
	return (count);
}

static int	ft_free_mem(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	*start;
	size_t	i;

	res = (char **)malloc((ft_size_of_mem((char *)s, c) + 1) * sizeof(char *));
	if (!s || !res)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == c)
		{
			s++;
			continue ;
		}
		start = (char *)s;
		while (*s && *s != c)
			s++;
		res[i] = ft_substr(start, 0, s - start);
		if (!res[i] && ft_free_mem(res))
			return (NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}
