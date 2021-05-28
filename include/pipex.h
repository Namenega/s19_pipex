/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:42:50 by pyg               #+#    #+#             */
/*   Updated: 2021/05/28 15:16:33 by pyg              ###   ########.fr       */
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

typedef struct	s_pip
{
	int	i;
}				t_pip;


int		main(int ac, char **av, char **envp);
void	error_msg(char *s);
char	*parse_arg(char *s);
int		lets_open_r(char *av, int fd);
int		lets_open_w(char *av, int fd);

void	cmd_1(char *cmd, int fd[2], int pipex[2], char **envp);
void	cmd_2(char *cmd, int fd[2], int pipex[2], char **envp);
void	execute(char **cmd, char **envp);

#endif