/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 08:32:27 by hyoh              #+#    #+#             */
/*   Updated: 2022/09/29 12:54:16 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_blank_num(t_info info)
{
	int	num;

	num = info.width - info.zero - (info.len + info.pre);
	if (num < 0)
		num = 0;
	return (num);
}

int	print_ptr(uintptr_t var, t_info info, long long *ret)
{
	info.len = hexlen(&info, var);
	info.zero = 0;
	info.blank = get_blank_num(info);
	*ret += info.len + info.blank + info.pre;
	if (*ret >= 2147483647)
		return (-1);
	if (info.flag[3] == 1)
	{
		write(1, "0x", 2);
		ft_putnbr_base(var, info, ret);
		ft_putchar(' ', info.blank, info, ret);
	}
	else
	{
		ft_putchar(' ', info.blank, info, ret);
		write(1, "0x", 2);
		ft_putnbr_base(var, info, ret);
	}
	return (0);
}

int	print_percent(t_info info, long long *ret)
{
	info.blank = info.width - 1;
	if (info.blank < 0)
		info.blank = 0;
	*ret += info.blank + 1;
	if (*ret >= 2147483647)
		return (-1);
	if (info.flag[3] == 1)
	{
		write(1, "%", 1);
		ft_putchar(' ', info.blank, info, ret);
	}
	else
	{
		ft_putchar(' ', info.blank, info, ret);
		write(1, "%", 1);
	}
	return (0);
}

int	run(va_list ap, t_info info, long long *ret)
{
	int	r;

	r = 0;
	if (info.specifier == 'd' || info.specifier == 'i')
		r = print_int(va_arg(ap, int), info, ret);
	else if (info.specifier == 'u')
		r = print_uin(va_arg(ap, unsigned int), info, ret);
	else if (info.specifier == 'x' || info.specifier == 'X')
		r = print_hex(va_arg(ap, unsigned int), info, ret);
	else if (info.specifier == 'c')
		r = print_cha(va_arg(ap, int), info, ret);
	else if (info.specifier == 's')
		r = print_str(va_arg(ap, char *), info, ret);
	else if (info.specifier == 'p')
		r = print_ptr(va_arg(ap, uintptr_t), info, ret);
	else if (info.specifier == '%')
		r = print_percent(info, ret);
	if (r == -1 || *ret >= 2147483647)
	{
		*ret = -1;
		return (-1);
	}
	return (0);
}

int	ft_printf(const char *fix, ...)
{
	long long	ret;
	t_info		info;
	va_list		ap;

	va_start(ap, fix);
	ret = 0;
	while (*fix != '\0')
	{
		if (*fix != '%')
		{
			write(1, fix++, 1);
			ret++;
		}
		else
		{
			flag_check(&fix, info.flag);
			width_check(ap, &fix, &info);
			preci_check(ap, &fix, &info);
			info.specifier = *fix++;
			if (check(&info, &ret) == -1 || run(ap, info, &ret) == -1)
				break ;
		}
	}
	va_end(ap);
	return (ret);
}
