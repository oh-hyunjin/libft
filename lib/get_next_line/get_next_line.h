/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 09:45:43 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/18 14:53:44 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		ft_strlen2(char *str);
char	*ft_strjoin2(char *s1, char *s2);
int		find_n(char *str);
char	*substr(char *src, int len);
char	*get_line(char *read_line);
char	*get_backup(char *read_line);
char	*ft_read(int fd, char *backup);
char	*get_next_line(int fd);

#endif