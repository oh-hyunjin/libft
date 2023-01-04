/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_for_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:35:41 by hyoh              #+#    #+#             */
/*   Updated: 2023/01/04 14:49:10 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_in_env(t_info info, char **paths, char *cmd)
{
	char	*slash_cmd;
	char	*true_path;
	int		i;

	if (paths == NULL)
		exit(EXIT_FAILURE);
	slash_cmd = ft_strjoin("/", cmd);
	i = -1;
	while (paths[++i] != NULL)
	{
		true_path = ft_strjoin(paths[i], slash_cmd);
		if (!true_path)
		{
			double_free(paths, i);
			exit(EXIT_FAILURE);
		}
		if (access(true_path, X_OK) == 0)
			return (true_path);
		free(true_path);
	}
	free(slash_cmd);
	double_free(paths, i);
	error_exit(info.exe_file, cmd, 127);
	return (0);
}

char	*get_path(t_info info, char *cmd)
{
	int	i;

	if (cmd == NULL)
		error_exit(info.exe_file, cmd, 127);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = -1;
	while (info.env[++i] != NULL)
		if (ft_strnstr(info.env[i], "PATH=", 10) != NULL)
			break ;
	if (info.env[i] == NULL)
		exit(EXIT_FAILURE);
	return (find_in_env(info, ft_split(info.env[i] + 5, ':'), cmd));
}

char	**parse_cmd(char *before)
{
	char	**after;
	int		quote_flag;
	int		i;

	after = ft_split(before, ' ');
	if (!after)
		exit(EXIT_FAILURE);
	i = -1;
	quote_flag = 0;
	while (after[++i] != NULL)
	{
		if (!quote_flag && (after[i][0] == '\'' || after[i][0] == '\"'))
		{
			quote_flag = 1;
			after[i] = ft_substr(before, 1, ft_strlen(before) - 2);
			continue ;
		}
		if (quote_flag == 1)
		{
			after[i] = NULL;
			free(after[i]);
		}
		before += (ft_strlen(after[i]) + 1);
	}
	return (after);
}
