/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:21:12 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/04/12 11:21:16 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_of_digits(int n)
{
	int	digits;

	digits = 1;
	if (n < 0)
	{
		digits++;
		n = -n;
	}
	while (n >= 10)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

static char	*ft_handle_edge_case(void)
{
	char	*res;

	res = (char *)malloc(12 * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, "-2147483648", 12);
	return (res);
}

static char	*ft_convert_to_string(int n, int res_len)
{
	int		i;
	int		num;
	char	*res;

	res = (char *)malloc((res_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = res_len - 1;
	num = n;
	if (num < 0)
	{
		res[0] = '-';
		num = -num;
	}
	while (num >= 10)
	{
		res[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	res[i] = (num % 10) + '0';
	res[res_len] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	int		res_len;

	if (n == -2147483648)
		return (ft_handle_edge_case());
	res_len = ft_num_of_digits(n);
	return (ft_convert_to_string(n, res_len));
}
