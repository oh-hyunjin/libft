/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 09:45:49 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/29 15:04:54 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen2(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	int		i;
	char	*tmp;

	if (s1 == NULL)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = '\0';
	}
	tmp = (char *)malloc(sizeof(char) * (ft_strlen2(s1) + ft_strlen2(s2) + 1));
	if (tmp == 0)
		return (0);
	i = -1;
	while (s1[++i] != 0)
		tmp[i] = s1[i];
	while (*s2 != 0)
		tmp[i++] = *s2++;
	tmp[i] = 0;
	free(s1);
	return (tmp);
}

int	find_n(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*substr(char *src, int len)
{
	int		i;
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	i = 0;
	while (i < len)
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
