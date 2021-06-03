/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 12:24:14 by pyg               #+#    #+#             */
/*   Updated: 2021/06/03 14:07:31 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*parse_entire_path(char *cmd_0, char *directory)
{
	char	*path;
	char	*entire_path;

	if (directory[ft_strlen(directory) - 1] == '/')
		path = ft_strdup(directory);
	else
		path = ft_strjoin(directory, "/");
	if (path == NULL)
		error_msg("Entire path Error: Cant get entire directory path");
	entire_path = ft_strjoin(path, cmd_0);
	if (entire_path == NULL)
		error_msg("Entire path Error: path is empty");
	free(path);
	return (entire_path);
}

static char	*parse_path(t_pipex *pipex, char *cmd_0)
{
	size_t	index;
	char	**directories;
	char	*path;

	index = 0;
	directories = ft_split(pipex->path, ':');
	if (directories == NULL)
		error_msg("Split Error: Can't get directories");
	while (directories[index])
	{
		path = parse_entire_path(cmd_0, directories[index]);
		pipex->directory_fd = open(path, O_RDONLY);
		printf("dir_fd = [%d]\n", pipex->directory_fd);
		if (pipex->directory_fd == -1)
			free(path);
		else
		{
			ft_free_split(directories);
			close(pipex->directory_fd);
			return (path);
		}
		index++;
	}
	ft_free_split(directories);
	return (error_msg_2(pipex, "Error"));
}

char	*pathing(t_pipex *pipex, char *cmd_0)
{
	char	*path;
	int		absolute_path;

	absolute_path = 0;
	if (cmd_0[0] == '/' || cmd_0[0] == '.' || cmd_0[0] == '~')
		absolute_path = 1;
	if (absolute_path == 1)
	{
		path = ft_strdup(cmd_0);
		if (path == NULL)
			error_msg("Pathing Error : Path is NULL");
		return (path);
	}
	return (parse_path(pipex, cmd_0));
}