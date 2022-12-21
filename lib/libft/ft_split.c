/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:44:05 by hyoh              #+#    #+#             */
/*   Updated: 2022/07/15 16:12:41 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	res[i] = 0;
	return (res);
}
