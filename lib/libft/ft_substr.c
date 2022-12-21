/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 10:28:01 by hyoh              #+#    #+#             */
/*   Updated: 2022/07/18 15:19:48 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	slen;
	size_t	mlen;

	slen = ft_strlen(s);
	if (slen <= start)
		return (ft_strdup(""));
	mlen = len;
	if (slen < len)
		mlen = slen;
	res = (char *)malloc(sizeof(char) * (mlen + 1));
	if (res == 0)
		return (0);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}
