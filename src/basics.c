/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:37:57 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/13 01:24:04 by vtrofyme         ###   ########.fr       */
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		diff;
	size_t	index;

	diff = 0;
	index = 0;
	while (*s1 && *s2 && index < n)
	{
		if (*s1 != *s2)
		{
			diff = (unsigned char)*s1 - (unsigned char)*s2;
			return (diff);
		}
		s1++;
		s2++;
		index++;
	}
	if (index < n)
		diff = (unsigned char)*s1 - (unsigned char)*s2;
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

int	ft_is_space(char c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (0);
	return (1);
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

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
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
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	len_s;
	size_t	i;

	len_s = ft_strlen(s);
	if (start >= len_s)
		len = 0;
	if (len_s - start < len)
		len = len_s - start;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
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
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	total_len;
	size_t	s1_len;
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	total_len = s1_len + ft_strlen(s2);
	str = (char *)malloc((total_len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < total_len)
	{
		if (i < s1_len)
			str[i] = s1[i];
		else
			str[i] = s2[i - s1_len];
		i++;
	}
	str[i] = '\0';
	return (str);
}
