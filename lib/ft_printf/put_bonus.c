/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:42:34 by hyoh              #+#    #+#             */
/*   Updated: 2022/09/28 16:05:35 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int len, long long num, long long *ret)
{
	char	c;

	if (len == 0)
		return ;
	if (num < 0)
		num = -num;
	if (num >= 10)
		ft_putnbr(len, num / 10, ret);
	c = num % 10 + '0';
	write(1, &c, 1);
}

void	ft_putchar(char a, int num, t_info info, long long *ret)
{
	if (info.flag[4])
		a = '0';
	while (num-- > 0)
	{
		if (*ret >= 2147483647)
			return ;
		write(1, &a, 1);
	}
}

void	ft_putsign(int var, t_info *info)
{
	if (var < 0)
		write(1, "-", 1);
	else if (var >= 0 && (info -> flag[1] == 1 || info ->flag[2] == 1))
	{
		if (info -> flag[1] == 1)
			write(1, "+", 1);
		else if (info -> flag[2] == 1)
			write(1, " ", 1);
	}
	return ;
}

void	ft_putprefix(unsigned long var, t_info info)
{
	if (!info.flag[0] || var == 0)
		return ;
	if (info.specifier == 'x')
		write(1, "0x", 2);
	else if (info.specifier == 'X')
		write(1, "0X", 2);
}

void	ft_putnbr_base(unsigned long var, t_info info, long long *ret)
{
	char	num;
	char	*base;

	if (info.precision == 0 && var == 0)
		return ;
	base = "0123456789abcdef";
	if (var >= 16)
		ft_putnbr_base(var / 16, info, ret);
	num = base[var % 16];
	if (info.specifier == 'X' && ('a' <= num && num <= 'z'))
		num = num - 'a' + 'A';
	write(1, &num, 1);
}
