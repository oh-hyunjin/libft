/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:46:59 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/18 14:54:42 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	intlen(t_info *info, long num)
{
	int	len;

	info->pre = 0;
	if (num >= 0 && (info->flag[1] || info->flag[2]))
		info->pre = 1;
	if (info->precision == 0 && num == 0)
		return (0);
	if (num < 0)
	{
		info->pre = 1;
		num = -num;
	}
	len = 1;
	while (num >= 10)
	{
		num /= 10;
		len++;
	}
	return (len);
}

int	uintlen(t_info *info, unsigned int num)
{
	int	len;

	info->pre = 0;
	len = 1;
	while (num >= 10)
	{
		num /= 10;
		len++;
	}
	if (info->precision == 0 && num == 0)
		len = 0;
	return (len);
}

int	hexlen(t_info *info, unsigned long num)
{
	int	len;

	info->pre = 0;
	if (info->specifier == 'p')
		info->pre = 2;
	else
	{
		if (info->precision == 0 && num == 0)
			return (0);
		if (num != 0 && info->flag[0])
			info->pre = 2;
	}
	len = 1;
	while (num >= 16)
	{
		num /= 16;
		len++;
	}
	return (len);
}

int	ft_strlen3(t_info *info, void *var)
{
	char	*str;
	int		len;

	info->pre = 0;
	str = var;
	if (str == NULL)
		len = 6;
	else
	{
		len = 0;
		while (*str++)
			len++;
	}
	if (info->precision != -1 && info->precision < len)
		len = info->precision;
	return (len);
}

int	get_zero_num(t_info info)
{
	int	num;

	num = info.precision - info.len;
	if (num < 0)
		return (0);
	return (num);
}
