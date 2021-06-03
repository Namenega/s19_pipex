/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 12:03:14 by pyg               #+#    #+#             */
/*   Updated: 2021/06/03 14:20:11 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_w(char *av, t_pipex *pipex)
{
	pipex->outfile = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->outfile == -1)
		error_msg("Outfile Error: fail to open and write");
}

void	open_r(char *av, t_pipex *pipex)
{
	pipex->infile = open(av, O_RDONLY);
	if (pipex->infile == -1)
		error_msg("Infile Error: fail to open and read");
}
