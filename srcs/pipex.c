/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:42:06 by pyg               #+#    #+#             */
/*   Updated: 2021/06/03 17:32:19 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** pipe() replace |
** if we have smtg like "cmd_1 | cmd_2"
** the result of cmd_1 will be kinda stocked in the |
** cmd_2 will apply on the |.
*/

#include "../include/pipex.h"

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

static char	*get_env_path(char **envp)
{
	size_t	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
		{
			return (ft_substr(envp[index], 5, ft_strlen(envp[index])));
		}
		index++;
	}
	error_msg("Envp Error: PATH environement undefined");
	return (NULL);
}

static t_pipex	get_argv(char **av, char **envp)
{
	t_pipex		pipex;

	ft_memset(&pipex, 0, sizeof(pipex));
	pipex.infile = open_r(av[1]);
	pipex.outfile = open_w(av[4]);
	pipex.cmd1 = av[2];
	pipex.cmd2 = av[3];
	pipex.path = get_env_path(envp);
	if (pipex.path == NULL)
		error_msg("Path Error: No path");
	pipex.envp = envp;
	return(pipex);
}

int			main(int ac, char **av, char **envp)
{
	t_pipex		pipex;
	if (ac != 5)
		error_msg("ArgNum Error: ./pipex infile cmd1 cmd2 outfile");
	pipex = get_argv(av, envp);
	if (pipe(pipex.pipefd) == -1)
		error_msg("Pipe Error: pipe() returned -1");
	cmd_1(&pipex);
	cmd_2(&pipex);
	free(pipex.path);
}
