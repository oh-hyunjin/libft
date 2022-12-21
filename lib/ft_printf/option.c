/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:40:01 by hyoh              #+#    #+#             */
/*   Updated: 2022/09/29 09:54:57 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_check(const char **fix, int flag[])
{
	int	i;

	(*fix)++;
	i = 0;
	while (i < 5)
		flag[i++] = 0;
	while (**fix == '-' || **fix == '0' || **fix == '#' \
						|| **fix == ' ' || **fix == '+')
	{
		if (**fix == '#')
			flag[0] = 1;
		if (**fix == '+')
			flag[1] = 1;
		if (**fix == ' ')
			flag[2] = 1;
		if (**fix == '-')
			flag[3] = 1;
		if (**fix == '0')
			flag[4] = 1;
		(*fix)++;
	}
}

void	width_check(va_list ap, const char **fix, t_info *info)
{
	int	w;

	w = 0;
	if ('0' <= **fix && **fix <= '9')
	{
		while ('0' <= **fix && **fix <= '9')
		{
			w = 10 * w + (**fix - '0');
			(*fix)++;
		}
	}
	else if (**fix == '*')
	{
		(*fix)++;
		w = va_arg(ap, int);
	}
	info -> width = w;
}

void	preci_check(va_list ap, const char **fix, t_info *info)
{
	int	p;

	p = 0;
	if (**fix != '.')
		info -> precision = -1;
	else
	{
		(*fix)++;
		if ('0' <= **fix && **fix <= '9')
		{
			while ('0' <= **fix && **fix <= '9')
			{
				p = p * 10 + (**fix - '0');
				(*fix)++;
			}
		}
		else if (**fix == '*')
		{
			p = va_arg(ap, int);
			(*fix)++;
		}
		info -> precision = p;
	}
}

int	check(t_info *info, long long *ret)
{
	if (info->flag[3] == 1)
		info->flag[4] = 0;
	if (info->width < 0)
	{
		info->width = -(info->width);
		info->flag[3] = 1;
	}
	if (info->precision < 0)
		info->precision = -1;
	if (info->precision != -1)
		info->flag[4] = 0;
	if (*ret == -1 || *ret >= 2147483647)
		return (-1);
	return (0);
}
