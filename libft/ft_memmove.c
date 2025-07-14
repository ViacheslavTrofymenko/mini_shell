/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:28:21 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/04/08 15:28:23 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*c_src;
	unsigned char	*c_dest;
	size_t			i;

	c_src = (unsigned char *) src;
	c_dest = (unsigned char *) dest;
	i = 0;
	if (!dest && !src)
		return (0);
	if (c_dest > c_src)
	{
		while (n-- > 0)
		{
			c_dest[n] = c_src[n];
		}
	}
	else
	{
		while (i < n)
		{
			c_dest[i] = c_src[i];
			i++;
		}
	}
	return (dest);
}
