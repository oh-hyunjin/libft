/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 10:45:44 by hyoh              #+#    #+#             */
/*   Updated: 2022/07/15 16:13:16 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
