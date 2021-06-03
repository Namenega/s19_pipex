/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:42:06 by pyg               #+#    #+#             */
/*   Updated: 2021/06/03 14:31:36 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** pipe() replace |
** if we have smtg like "cmd_1 | cmd_2"
** the result of cmd_1 will be kinda stocked in the |
** cmd_2 will apply on the |.
*/

#include "../include/pipex.h"


// static void	ft_pid_1(int pid_1, int fd[2], char *av, char **envp, int file_1)
// {
// 	char	**cmd;
// 	char	**paths;
// 	char	*path;

// 	paths = ft_split(ft_split(envp[0], '=')[1], ':');
// 	path = NULL;
// 	// printf("paths[0] for cmd_1 = [%s]\n", paths[0]);
// 	// printf("paths[1] for cmd_1 = [%s]\n", paths[1]);
// 	cmd = ft_split(av, ' ');
// 	if (pid_1 == -1)
// 		error_msg("Pid_1 Fork Error: fork() failed");
// 	if (pid_1 == 0)//child process (cmd_1)
// 	{
// 		//STDOUT_FILENO = 1
// 		//dup2 duplicate fd[1] into fd[2]
// 		//fd[2] will point at fd[1]
// 		dup2(file_1, STDIN_FILENO);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		while (*paths && path == NULL)
// 		{
// 			path = ft_strjoin(ft_strjoin(*paths, "/"), cmd[0]);
// 		}
// 		// printf("path for cmd_1 = [%s]\n", path);
// 		// execve(path, cmd, envp); //premier var = path genre /bin/ls -> get ca grace a (?)
// 		if (execve(path, cmd, envp) == -1)
// 			error_msg("Cmd_1 Error: Can't apply first command.");
// 	}
// }

// static void	ft_pid_2(int pid_2, int fd[2], char *av, char **envp, int file_2)
// {
// 	char	**cmd;
// 	char	**paths;
// 	char	*path;

// 	paths = ft_split(ft_split(envp[0], '=')[1], ':');
// 	path = NULL;
// 	cmd = ft_split(av, ' ');
// 	if (pid_2 == -1)
// 		error_msg("Pid_2 Fork Error: fork() failed");
// 	if (pid_2 == 0) //child process (cmd_2)
// 	{
// 		//STDIN_FILENO = 0
// 		dup2(fd[0], STDIN_FILENO);
// 		dup2(file_2, STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		while (*paths && path == NULL)
// 		{
// 			path = ft_strjoin(ft_strjoin(*paths, "/"), cmd[0]);
// 		}
// 		// printf("path for cmd_2 = [%s]\n", path);
// 		if (execve(path, cmd, envp) == -1)
// 			error_msg("Cmd_2 Error: Can't apply second command.");
// 	}
// }
char	*error_msg_2(t_pipex *pipex, char *s)
{
	ft_putstr_fd(s, 0);
	if (pipex->infile > 0)
		close(pipex->infile);
	if (pipex->outfile > 0)
		close(pipex->outfile);
	if (pipex->pipefd[0] > 0)
		close(pipex->pipefd[0]);
	if (pipex->pipefd[1] > 0)
		close(pipex->pipefd[1]);
	exit(EXIT_FAILURE);
}

void	error_msg(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

// int main(int ac, char **av, char **envp)
// {
// 	int fd[2];
// 	int	file[2];
// 	int	pid_1;
// 	int	pid_2;

// 	if (ac != 5)
// 		error_msg("ArgNum Error: ./pipex infile cmd1 cmd2 outfile");
// 	if (pipe(fd) == -1)
// 		error_msg("Pipe Error: pipe failed");
// 	file[0] = open_r(av[1], file[0]);
// 	file[1] = open_w(av[4], file[1]);
// 	pid_1 = fork();
// 	ft_pid_1(pid_1, fd, av[2], envp, file[0]);
// 	pid_2 = fork();
// 	ft_pid_2(pid_2, fd, av[3], envp, file[1]);
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid_1, NULL, 0);
// 	waitpid(pid_2, NULL, 0);
// 	return (0);
// }

static char	*get_env_path(char **envp)
{
	size_t	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
			return (ft_substr(envp[index], 5, ft_strlen(envp[index])));
		index++;
	}
	error_msg("Envp Error: PATH environement undefined");
	return (NULL);
}

static void	get_argv(char **av, char **envp, t_pipex *pipex)
{
	// size_t	index;

	// index = 0;
	open_r(av[1], pipex);
	pipex->cmd1 = av[2];
	pipex->cmd2 = av[3];
	open_w(av[4], pipex);

	pipex->path = get_env_path(envp);
	// while (envp[index])
	// {
	// 	if (!ft_strncmp(envp[index], "PATH=", 5))
	// 	{
	// 		pipex->path = ft_substr(envp[index], 5, ft_strlen(envp[index]));
	// 		// pipex->path = envp[index + 5];
	// 		break ;
	// 	}
	// 	index++;
	// }

	printf("p->path = [%s]\n", pipex->path);

	if (pipex->path == NULL)
		error_msg("Path Error: No path");
	pipex->envp = envp;
}

int			main(int ac, char **av, char **envp)
{
	t_pipex		*pipex;
	
	pipex = ft_calloc_2(sizeof(pipex));
	if (ac != 5)
		error_msg("ArgNum Error: ./pipex infile cmd1 cmd2 outfile");
	get_argv(av, envp, pipex);
	if (pipe(pipex->pipefd) == -1)
		error_msg("Pipe Error: pipe() returned -1");
	cmd_1(pipex);
	cmd_2(pipex);
	free(pipex->path);
}
