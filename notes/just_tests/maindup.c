/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maindup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:09 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/14 14:18:30 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

void	testfunction(void)
{
	char	buffer;
	int		readinfo;

	readinfo = 1;
	while (readinfo)
	{
		readinfo = read(0, &buffer, 1);
		if (readinfo)
			write(1, &buffer, 1);
	}
}

int	main(void)
{
	int		fd_in = open("file.txt", O_RDONLY);
	int		fd_out = open("outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int		fd_stock[2];
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];
	int		reswait[2];

	fd_stock[0] = dup(STDIN_FILENO);
	fd_stock[1] = dup(STDOUT_FILENO);
	pipe(pipe_fd);
	pid1 = fork();
	if (!pid1)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		testfunction();
		close (pipe_fd[0]);
		exit(0);
	}
	close (pipe_fd[1]);
	pid2 = fork();
	if (!pid2)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		testfunction();
		close (pipe_fd[0]);
		exit(0);
	}
	waitpid(pid1, &reswait[0], 0);
	waitpid(pid2, &reswait[1], 0);
	dup2 (fd_stock[0], STDIN_FILENO);
	dup2 (fd_stock[1], STDOUT_FILENO);
	dprintf(1, "wait1 = %d | wait2 = %d\n", reswait[0], reswait[1]);
	close (fd_stock[0]);
	close (fd_stock[1]);
	close (fd_in);
	close (fd_out);
	return (0);
}

//Solution au système de fd, à transformer en boucle selon le nombre de commande à exécuter