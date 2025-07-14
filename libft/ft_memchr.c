/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:32:15 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/04/10 14:32:17 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr_s;
	unsigned char	char_c;

	i = 0;
	ptr_s = (unsigned char *)s;
	char_c = (unsigned char)c;
	while (i < n)
	{
		if (ptr_s[i] == char_c)
			return ((void *)(ptr_s + i));
		i++;
	}
	return (NULL);
}
