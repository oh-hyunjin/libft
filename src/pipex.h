/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:38:56 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/22 17:49:27 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ 0
# define WRITE 1

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/get_next_line/get_next_line.h"
# include <unistd.h> // 지워도 되나
# include <stdio.h> // 지우기
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_children{
	int	pid;
}	t_children;


#endif