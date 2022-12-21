/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:48:08 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/18 14:54:36 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

typedef struct s_info
{
	int		flag[5];
	int		width;
	int		precision;
	char	specifier;
	int		len;
	int		pre;
	int		zero;
	int		blank;
}	t_info;

int		ft_printf(const char *fix, ...);
int		run(va_list ap, t_info info, long long *ret);
int		print_ptr(uintptr_t var, t_info info, long long *ret);
int		print_percent(t_info info, long long *ret);
int		get_blank_num(t_info info);
void	flag_check(const char **fix, int flag[]);
void	width_check(va_list ap, const char **fix, t_info *info);
void	preci_check(va_list ap, const char **fix, t_info *info);
int		check(t_info *info, long long *ret);
int		print_int(int var, t_info info, long long *ret);
int		print_uin(unsigned int var, t_info info, long long *ret);
int		print_hex(unsigned int var, t_info info, long long *ret);
int		print_cha(char var, t_info info, long long *ret);
int		print_str(char *var, t_info info, long long *ret);
void	ft_putnbr(int len, long long num, long long *ret);
void	ft_putchar(char a, int num, t_info info, long long *ret);
void	ft_putsign(int var, t_info *info);
void	ft_putprefix(unsigned long var, t_info info);
void	ft_putnbr_base(unsigned long var, t_info info, long long *ret);
int		intlen(t_info *info, long num);
int		uintlen(t_info *info, unsigned int num);
int		hexlen(t_info *info, unsigned long num);
int		ft_strlen3(t_info *info, void *var);
int		get_zero_num(t_info info);

#endif