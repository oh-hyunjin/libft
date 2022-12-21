/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 09:09:58 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/18 14:54:53 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_int(int var, t_info info, long long *ret)
{
	info.len = intlen(&info, var);
	info.zero = get_zero_num(info);
	info.blank = get_blank_num(info);
	*ret += info.len + info.zero + info.blank + info.pre;
	if (*ret >= 2147483647)
		return (-1);
	if (info.flag[3] == 1)
	{
		ft_putsign(var, &info);
		ft_putchar('0', info.zero, info, ret);
		ft_putnbr(info.len, var, ret);
		ft_putchar(' ', info.blank, info, ret);
	}
	else
	{
		if (!info.flag[4])
			ft_putchar(' ', info.blank, info, ret);
		ft_putsign(var, &info);
		if (info.flag[4])
			ft_putchar(' ', info.blank, info, ret);
		ft_putchar('0', info.zero, info, ret);
		ft_putnbr(info.len, var, ret);
	}
	return (0);
}

int	print_uin(unsigned int var, t_info info, long long *ret)
{
	info.len = uintlen(&info, var);
	info.zero = get_zero_num(info);
	info.blank = get_blank_num(info);
	*ret += info.len + info.zero + info.blank;
	if (*ret >= 2147483647)
		return (-1);
	if (info.flag[3] == 1)
	{
		ft_putchar('0', info.zero, info, ret);
		ft_putnbr(info.len, var, ret);
		ft_putchar(' ', info.blank, info, ret);
	}
	else
	{
		ft_putchar(' ', info.blank, info, ret);
		ft_putchar('0', info.zero, info, ret);
		ft_putnbr(info.len, var, ret);
	}
	return (0);
}

int	print_hex(unsigned int var, t_info info, long long *ret)
{
	info.len = hexlen(&info, var);
	info.zero = get_zero_num(info);
	info.blank = get_blank_num(info);
	*ret += info.len + info.zero + info.blank + info.pre;
	if (*ret >= 2147483647)
		return (-1);
	if (info.flag[3])
	{
		ft_putprefix(var, info);
		ft_putchar('0', info.zero, info, ret);
		ft_putnbr_base(var, info, ret);
		ft_putchar(' ', info.blank, info, ret);
	}
	else
	{
		if (!info.flag[4])
			ft_putchar(' ', info.blank, info, ret);
		ft_putprefix(var, info);
		if (info.flag[4])
			ft_putchar(' ', info.blank, info, ret);
		ft_putchar('0', info.zero, info, ret);
		ft_putnbr_base(var, info, ret);
	}
	return (0);
}

int	print_cha(char var, t_info info, long long *ret)
{
	info.blank = info.width - 1;
	if (info.blank < 0)
		info.blank = 0;
	*ret += info.blank + 1;
	if (*ret >= 2147483647)
		return (-1);
	if (info.flag[3] == 1)
	{
		write(1, &var, 1);
		ft_putchar(' ', info.blank, info, ret);
	}
	else
	{
		ft_putchar(' ', info.blank, info, ret);
		write(1, &var, 1);
	}
	return (0);
}

int	print_str(char *var, t_info info, long long *ret)
{
	info.len = ft_strlen3(&info, var);
	info.zero = 0;
	info.blank = get_blank_num(info);
	*ret += info.len + info.blank;
	if (*ret >= 2147483647)
		return (-1);
	if (info.flag[3] == 1)
	{
		if (var == NULL)
			write(1, "(null)", info.len);
		else
			write(1, var, info.len);
		ft_putchar(' ', info.blank, info, ret);
	}
	else
	{
		ft_putchar(' ', info.blank, info, ret);
		if (var == NULL)
			write(1, "(null)", info.len);
		else
			write(1, var, info.len);
	}
	return (0);
}
