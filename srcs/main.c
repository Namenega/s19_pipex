/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyg <pyg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:42:06 by pyg               #+#    #+#             */
/*   Updated: 2021/05/27 22:58:57 by pyg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*parse_arg(char *s)
{
	char	*new_s;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (s[0] == '"')
	{
		new_s = malloc(sizeof(char) * (ft_strlen(s) - 1));
		if (!new_s)
			return (NULL);
		while (s[j] && s[j] != '"')
		{
			new_s[i] = s[j];
			i++;
			j++;
		}
		new_s[i] = '\0';
		return (new_s);
	}
	else
		return (s);
}


void	error_msg(char *s)
{
	perror(s);
	// ft_putstr_fd(s, 1);
	// ft_putchar_fd('\n', 1);
	exit(EXIT_FAILURE);
}

int		main(int ac, char **av)
{
	//int		pipex[4];
	int		fd;

	if (ac != 5)
		error_msg("ArgNum Error: ./pipex infile cmd1 cmd2 outfile");
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_msg("Arg_1 Error: File doesnt exist");
	av[2] = parse_argv(av[2]);
	av[3] = parse_argv(av[3]);
	printf("av2 = [%s]\n", av[2]);
	printf("av3 = [%s]\n", av[3]);
	close(fd);
	return (0);
}

// int main(int ac , char **av)
// {
//     int pipex[3]; //File descriptors
//     //int newfd;
//     int pidOne, pidTwo;

//     if (ac != 4)
//     {
//         fprintf(stderr, "usage: pipex cmd1 cmd2 cmd3\n");
//         exit(1);
//     }

//     if (pipe(pipex) == -1)
//         errorHandler("Unable to get pipe", 1);
    
//     //creating two new processes
//     if( (pidOne = fork()) == -1)
//         errorHandler("Cannot fork", 2);
    

//     if (pidOne > 0) {   /* Parent executes av[3] */
//         close(pipex[1]);/* Parent doesnt write to pipe */
//         if(dup2(pipex[0], 0) == -1)
//             errorHandler("Could not redirect std in", 3);
        
//         close(pipex[0]); /* stdin is duplicated so we close pipe */
//         execlp(av[3], av[3], NULL);
//         errorHandler(av[3], 4);

//         if( (pidTwo = fork()) == -1)
//             errorHandler("Cannot fork", 2);
    
//         if (pidTwo > 0) {   /* Parent executes av[2] */
//             if(dup2(pipex[1], 1) == -1)
//                 errorHandler("Could not redirect std in", 3);
        
//             close(pipex[0]); 
//             execlp(av[2], av[2], NULL);
//             errorHandler(av[2], 4);
//         }
//     }



//     if(dup2(pipex[0], 0) == -1)
//         errorHandler("Could not redirect std out", 4);
        
//     close(pipex[0]); 
//     execlp(av[1], av[1], NULL);
//     errorHandler(av[1], 5);
    

// }