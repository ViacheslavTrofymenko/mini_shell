/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:37:57 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/08 18:59:21 by ikulik           ###   ########.fr       */
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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	length;

	length = 0;
	index = 0;
	while (src[length])
		length++;
	if (size > 0)
	{
		while (src[index] && (index < size - 1))
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (length);
}

void	*ft_memset(void *s, char c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_intset(int	*arr, int c, int n)
{
	int	index;

	index = 0;
	while (index < n)
	{
		arr[index] = c;
		index++;
	}
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*iter;

	iter = *lst;
	if (iter)
		while (iter->next)
			iter = iter->next;
	iter->next = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*iter;
	t_list	*cleaner;

	iter = *lst;
	while (iter)
	{
		cleaner = iter;
		iter = iter->next;
		del(cleaner->content);
		free(cleaner);
	}
	*lst = NULL;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
