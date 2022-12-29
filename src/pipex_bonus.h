/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:38:56 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/28 16:45:26 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define READ 0
# define WRITE 1
# define OLD 0
# define NEW 1

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/get_next_line/get_next_line.h"
# include <unistd.h> // 지워도 되나
# include <stdio.h> // 지우기
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_cmd{
	int	num;
	int	idx;
}	t_cmd;

// libft_test.c
// char	*ft_strjoin(char const *s1, char const *s2);
// int		get_cnt(char const *s, char c);
// char	*ft_split_2(char const *s, char c, int start);
// char	**ft_split(char const *s, char c);
// char	*ft_strnstr(const char *haystack, const char *needle, size_t n);


#endif