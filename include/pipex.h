/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:42:50 by pyg               #+#    #+#             */
/*   Updated: 2021/05/27 22:56:43 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include "libft/libft.h"

typedef struct	s_pip
{
	int	i;
}				t_pip;


int		main(int ac, char **av);
void	error_msg(char *s);
char	*parse_arg(char *s);

#endif