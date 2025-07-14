/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:13:17 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/04/11 19:13:19 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	total_size;
	char	*ptr;

	if (nmemb != 0 && size != 0)
	{
		if (nmemb > SIZE_MAX / size)
			return (NULL);
		total_size = nmemb * size;
	}
	else
		total_size = 0;
	ptr = malloc(total_size);
	if (ptr)
	{
		i = 0;
		while (i < total_size)
		{
			ptr[i] = '\0';
			i++;
		}
	}
	return ((void *)ptr);
}
