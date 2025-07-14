/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:10:05 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/04/10 15:10:07 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_little;

	i = 0;
	len_little = 0;
	if (*little == '\0')
		return ((char *)big);
	while (little[len_little] != '\0')
		len_little++;
	while (i < len && big[i] != '\0')
	{
		if (len - i < len_little)
			return (NULL);
		j = 0;
		while (j < len_little && big[i + j] == little[j])
			j++;
		if (j == len_little)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
