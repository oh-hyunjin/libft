/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:38:56 by hyoh              #+#    #+#             */
/*   Updated: 2023/01/04 14:42:18 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define READ 0
# define WRITE 1
# define OLD 0
# define NEW 1

# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_cmd{
	int	cur;
	int	idx;
	int	last;
}	t_cmd;

typedef struct s_hd{
	int		flag;
	int		fd;
}	t_hd;

typedef struct s_info{
	int		argc;
	char	**argv;
	char	**env;
	char	*exe_file;
	char	*outfile;
	int		last_status;
	t_hd	hd;
}	t_info;

// pipex utils
void	error_exit(char *exe_file, char *cmd, int num);
void	double_free(char **target, int num);
int		get_heredoc(char **argv, t_hd *hd);
void	pipex_init(t_info *info, int pipe_fd[2][2], int *cmd_last);

// ready for exe
char	*find_in_env(t_info info, char **paths, char *cmd);
char	*get_path(t_info info, char *cmd);
char	**parse_cmd(char *before);

// pipex
void	first_cmd(t_info info, char *argv_cmd, int pipe_fd[]);
void	last_cmd(t_info info, char *argv_cmd, int pipe_fd[]);
void	other_cmd(t_info info, char *argv_cmd, int pipe_fd[2][2]);
void	make_proc(int pipe_fd[2][2], t_cmd *cmd, int *pid);

#endif