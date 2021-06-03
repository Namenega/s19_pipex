/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:42:50 by pyg               #+#    #+#             */
/*   Updated: 2021/06/03 13:10:52 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft/libft.h"

typedef struct	s_pipex
{
	int		infile;
	int		outfile;
	char	*cmd1;
	char	*cmd2;
	int		pipefd[2];
	pid_t	pid_1;
	pid_t	pid_2;
	char	**envp;
	char	*path;
	int		directory_fd;
}				t_pipex;

/*
** PIPEX_C
*/

int		main(int ac, char **av, char **envp);
void	error_msg(char *s);
char	*error_msg_2(t_pipex *pipex, char *s);


/*
** OPEN_C
*/

void	open_r(char *av, t_pipex *pipex);
void	open_w(char *av, t_pipex *pipex);


/*
** CMD_C
*/

int		cmd_1(t_pipex *pipex);
int		cmd_2(t_pipex *pipex);

/*
** PATHING_C
*/

char	*pathing(t_pipex *pipex, char *cmd_0);

#endif