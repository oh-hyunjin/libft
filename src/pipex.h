/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:38:56 by hyoh              #+#    #+#             */
/*   Updated: 2023/01/04 08:45:17 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ 0
# define WRITE 1
# define OLD 0
# define NEW 1

# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"
# include <unistd.h> // 지워도 되나
# include <stdio.h> // 지우기
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_cmd{
	int	num;
	int	idx;
}	t_cmd;


void	first_cmd(char *file, char *argv_cmd, char **env, int pipe_fd[]);
void	last_cmd(char *file, char *argv_cmd, char **env, int pipe_fd[]);
void	make_proc(int argc, int pipe_fd[2], int *cmd_num, int *pid);
void	error_exit(int num);
char	*get_path(char *cmd, char **env);
char	**parse_cmd(char *before);



#endif