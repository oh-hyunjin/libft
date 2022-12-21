/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:47:24 by hyoh              #+#    #+#             */
/*   Updated: 2022/07/18 11:59:04 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dp;
	const unsigned char	*sp;
	size_t				i;

	if (dst == 0 && src == 0)
		return (0);
	dp = dst;
	sp = src;
	if (dst < src)
	{
		while (len--)
			*dp++ = *sp++;
	}
	else
	{
		i = 0;
		while (i < len)
		{
			dp[len - 1 - i] = sp[len - 1 - i];
			i++;
		}
	}
	return (dst);
}
