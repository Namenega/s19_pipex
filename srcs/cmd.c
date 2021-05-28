/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:32:27 by pyg               #+#    #+#             */
/*   Updated: 2021/05/28 15:58:43 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute(char **cmd, char **envp)
{
	char	**file_paths;
	char	*path;
	char	*tmp;
	struct stat	buf;

	path = NULL;
	file_paths = ft_split(ft_split(envp[0], '=')[1], ':');
	while (path == NULL && *file_paths)
	{
		tmp = ft_strjoin(ft_strjoin(*file_paths, "/"), cmd[0]);
		if (stat(tmp, &buf) == 0)
			path = tmp;
		else
			file_paths++;
	}
	if (path == NULL)
		error_msg("Cmd Error: command not found");
	else
		execve(path, cmd, envp);
}

void	cmd_1(char *cmd, int fd[2], int pipex[2], char **envp)
{
	close(pipex[0]);
	dup2(pipex[1], 1);
	dup2(fd[0], 0);
	close(pipex[1]);
	execute(ft_split(cmd, ' '), envp);
}

void	cmd_2(char *cmd, int fd[2], int pipex[2], char **envp)
{
	close(pipex[1]);
	dup2(pipex[0], 0);
	dup2(fd[1], 1);
	close(pipex[0]);
	execute(ft_split(cmd, ' '), envp);
}