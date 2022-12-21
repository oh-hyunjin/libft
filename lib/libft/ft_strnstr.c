/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:41:29 by hyoh              #+#    #+#             */
/*   Updated: 2022/07/17 09:43:46 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
