/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:34:28 by hyoh              #+#    #+#             */
/*   Updated: 2022/07/19 11:51:19 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long			num;
	int					sign;
	unsigned long long	max;

	num = 0;
	sign = 1;
	max = 9223372036854775807;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		num = 10 * num + (*str - '0');
		str++;
	}
	if ((unsigned long long)num > max - 1 && sign == -1)
		return (0);
	if ((unsigned long long)num > max && sign == 1)
		return (-1);
	return ((int)num * sign);
}
