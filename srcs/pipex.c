/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:42:06 by pyg               #+#    #+#             */
/*   Updated: 2021/05/31 00:31:42 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** pipe() replace |
** if we have smtg like "cmd_1 | cmd_2"
** the result of cmd_1 will be kinda stocked in the |
** cmd_2 will apply on the |.
*/

#include "../include/pipex.h"

static int		lets_open_w(char *av, int file)
{
	file = open(av, O_WRONLY | O_CREAT, 0777);
	if (file < 0)
		error_msg("Outfile Error: fail to open and write");
	return (file);
}

static int		lets_open_r(char *av, int file)
{
	file = open(av, O_RDONLY);
	if (file < 0)
		error_msg("Infile Error: fail to open and read");
	return (file);
}

static void	ft_pid_1(int pid_1, int fd[2], char *av, char **envp, int file_1)
{
	char	**cmd;

	cmd = ft_split(av, ' ');
	if (pid_1 == -1)
		error_msg("Pid_1 Fork Error: fork() failed");
	if (pid_1 == 0)//child process (cmd_1)
	{
		//STDOUT_FILENO = 1
		//dup2 duplicate fd[1] into fd[2]
		//fd[2] will point at fd[1]
		dup2(file_1, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(cmd[0], cmd, envp);
	}
}

static void	ft_pid_2(int pid_2, int fd[2], char *av, char **envp, int file_2)
{
	char **cmd;

	cmd = ft_split(av, ' ');
	if (pid_2 == -1)
		error_msg("Pid_2 Fork Error: fork() failed");
	if (pid_2 == 0) //child process (cmd_2)
	{
		//STDIN_FILENO = 0
		dup2(fd[0], STDIN_FILENO);
		dup2(file_2, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(cmd[0], cmd, envp);
	}
}

void	error_msg(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

int main(int ac, char **av, char **envp)
{
	int fd[2];
	int	file[2];
	int	pid_1;
	int	pid_2;

	if (ac != 5)
		error_msg("ArgNum Error: ./pipex infile cmd1 cmd2 outfile");
	if (pipe(fd) == -1)
		error_msg("Pipe Error: pipe failed");
	file[0] = lets_open_r(av[1], file[0]);
	file[1] = lets_open_w(av[4], file[1]);
	pid_1 = fork();
	ft_pid_1(pid_1, fd, av[2], envp, file[0]);
	pid_2 = fork();
	ft_pid_2(pid_2, fd, av[3], envp, file[1]);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);
	return (0);
}
