/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:43:42 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/18 14:54:14 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	int				fd_num;
	char			*backup;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

void	del_node(t_list **head, t_list *node);
int		ft_strlen2(char *str);
char	*ft_strjoin2(char *s1, char *s2);
int		find_n(char *str);
char	*substr(char *src, int len);
char	*get_line(char *read_line);
char	*get_backup(char *read_line);
char	*ft_read(int fd, char *backup);
t_list	*find_node(int fd, t_list **head);
char	*get_next_line(int fd);

#endif