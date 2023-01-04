/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:43:01 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/30 16:49:10 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(int num)
{
	if (num == 1)
		write(2, "pipex: input: No such file or directory\n", 40);
	else if (num == 2)
		write(2, "fork fail\n", 10);
	else if (num == 3)
		write(2, "pipe fail\n", 10);
	else if (num == 127)
	{
		write(2, "pipex: fizzBuzz: command not found\n", 35);
		exit(127);
	}
	exit(1);
}

char	*get_path(char *cmd, char **env)
{
	char	**paths;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (*env != NULL)
	{
		if (ft_strnstr(*env, "PATH=", 10) != NULL)
			break ;
		env++;
	}
	if (*env == NULL)
		return (0);
	*env += 5;
	paths = ft_split(*env, ':'); // free
	if (paths == NULL)
		return (0);
	while (*paths != NULL)
	{
		*paths = ft_strjoin(*paths, ft_strjoin("/", cmd));
		if (access(*paths, X_OK) == 0)
			break ;
		paths++;
	}
	return (*paths);
}

char	**parse_cmd(char *before)
{
	char	**after;
	char	*s_quote;
	int		quote_flag;
	int		i;

	s_quote = before;
	after = ft_split(before, ' ');
	i = -1;
	quote_flag = 0;
	while (after[++i] != NULL)
	{
		if (after[i][0] == '\'' || after[i][0] == '\"')
		{
			quote_flag = 1;
			after[i] = ft_substr(s_quote, 1, ft_strlen(s_quote) - 2);
			continue ;
		}
		if (quote_flag == 1)
			after[i] = NULL; //free(after[i]);????
		else
			s_quote += (ft_strlen(after[i]) + 1);
	}
	return (after);
}