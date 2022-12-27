/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:44:05 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/23 13:44:25 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*tmp;

	len1 = 0;
	len2 = 0;
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	tmp = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (tmp == 0)
		return (0);
	i = 0;
	while (*s1 != 0)
		tmp[i++] = *s1++;
	while (*s2 != 0)
		tmp[i++] = *s2++;
	tmp[i] = 0;
	return (tmp);
}

int	get_cnt(char const *s, char c)
{
	int	cnt;

	cnt = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			cnt++;
		while (*s && *s != c)
			s++;
	}
	return (cnt);
}

char	*ft_split_2(char const *s, char c, int start)
{
	int		len;
	int		i;
	char	*str;

	len = 0;
	while (s[start + len] != c && s[start + len] != 0)
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
		str[i++] = s[start++];
	str[i] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		cnt;
	int		i;
	int		start;
	char	**res;

	cnt = get_cnt(s, c);
	res = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (res == 0)
		return (0);
	i = 0;
	start = 0;
	while (i < cnt)
	{
		while (s[start] == c)
			start++;
		res[i] = ft_split_2(s, c, start);
		while (s[start] != c && s[start] != 0)
			start++;
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	t;

	if (needle[0] == 0)
		return ((char *)haystack);
	i = 0;
	while (i < n && haystack[i])
	{
		t = 0;
		if (haystack[i] == needle[t])
		{
			while (haystack[i + t] != 0 && \
					haystack[i + t] == needle[t] && i + t < n)
				t++;
			if (needle[t] == 0)
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (0);
}
