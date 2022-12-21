/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 10:00:24 by hyoh              #+#    #+#             */
/*   Updated: 2022/07/16 11:09:13 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	slen;
	size_t	i;

	slen = 0;
	while (s1[slen])
		slen++;
	ptr = (char *)malloc(sizeof(char) * (slen + 1));
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < slen)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
