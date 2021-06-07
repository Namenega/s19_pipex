/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 12:03:14 by pyg               #+#    #+#             */
/*   Updated: 2021/06/07 18:04:51 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	open_w(char *av)
{
	int	fd;

	fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		error_msg("Outfile Error: fail to open and write");
	return (fd);
}

int	open_r(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		error_msg("Infile Error: fail to open and read");
	return (fd);
}
