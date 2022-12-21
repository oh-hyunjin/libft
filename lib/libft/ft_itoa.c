/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:12:26 by hyoh              #+#    #+#             */
/*   Updated: 2022/07/19 11:51:35 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_size(int num)
{
	int	size;

	if (num == 0)
		return (1);
	size = 0;
	if (num < 0)
		size++;
	while (num)
	{
		num /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		size;
	char	*res;

	size = get_size(n);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (res == 0)
		return (0);
	res[size] = 0;
	sign = 1;
	if (n < 0)
	{
		sign = -1;
		res[0] = '-';
	}
	while (--size >= 0)
	{
		if (size == 0 && sign == -1)
			break ;
		res[size] = (n % 10 * sign + '0');
		n /= 10;
	}
	return (res);
}
