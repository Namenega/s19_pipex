/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 12:05:56 by pyg               #+#    #+#             */
/*   Updated: 2021/06/03 13:10:25 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int		cmd_1(t_pipex *pipex)
{
	char	**cmd;
	char	*binary;

	cmd = ft_split(pipex->cmd1, ' ');
	if (cmd == NULL)
		error_msg("Split Error: split failed in cmd_1");
	binary = pathing(pipex, cmd[0]);
	pipex->pid_1 = fork();
	if (pipex->pid_1 == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		execve(binary, cmd, pipex->envp);
		error_msg("Cmd_1 Error: execve failed");
	}
	waitpid(pipex->pid_1, NULL, 0);
	close(pipex->infile);
	close(pipex->pipefd[1]);
	pipex->pipefd[1] = -1;
	ft_free_split(cmd);
	free(binary);
	return (0);
}

int		cmd_2(t_pipex *pipex)
{
	char	**cmd;
	char	*binary;

	cmd = ft_split(pipex->cmd2, ' ');
	if (cmd == NULL)
		error_msg("Split Error: split failed in cmd_1");
	binary = pathing(pipex, cmd[0]);
	pipex->pid_2 = fork();
	if (pipex->pid_2 == 0)
	{
		dup2(pipex->pipefd[0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		execve(binary, cmd, pipex->envp);
		error_msg("Cmd_2 Error: execve failed");
	}
	waitpid(pipex->pid_2, NULL, 0);
	close(pipex->outfile);
	close(pipex->pipefd[0]);
	pipex->pipefd[0] = -1;
	ft_free_split(cmd);
	free(binary);
	return (0);
}
