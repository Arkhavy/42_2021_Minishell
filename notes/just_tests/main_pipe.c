/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:34:56 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/21 10:21:24 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

void	full_close(int fd_main[3], int pipe_fd[2])
{
	close(fd_main[0]);
	close(fd_main[1]);
	close(fd_main[2]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];
	int		fd_main[3];
	char	*split1[4] = {"cat", "-e", "main_pipe.c", NULL};
	char	*split2[3] = {"wc", "-l", NULL};

	(void)ac;
	(void)av;
	fd_main[0] = dup(STDIN_FILENO);
	fd_main[1] = dup(STDOUT_FILENO);
	fd_main[2] = dup(STDERR_FILENO);
	pipe(pipe_fd);
	pid1 = fork();
	if (!pid1)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		execve("/bin/cat", split1, env);
		exit(0);
	}
	dup2(fd_main[1], STDOUT_FILENO);
	pid2 = fork();
	if (!pid2)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		execve("/usr/bin/wc", split2, env);
		exit (0);
	}
	dup2(fd_main[0], STDIN_FILENO);
	dup2(fd_main[2], STDERR_FILENO);
	full_close(fd_main, pipe_fd);
	waitpid(pid1, 0, 0);
	waitpid(pid2, 0, 0);
	return (0);
}
