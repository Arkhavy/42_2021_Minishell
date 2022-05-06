/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_multi_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:21:40 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/21 10:38:24 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int	main(int ac, char **av, char **env)
{
	pid_t	*pid;
	size_t	a;
	int		pipe_fd1[2];
	int		pipe_fd2[2];
	int		fd_main[3];
	char	split[0][4] = {"cat", "-e", "main_pipe.c", NULL};
	char	split[1][3] = {"cat", "-e", NULL};
	char	split[2][3] = {"cat", "-e", NULL};
	char	split[3][3] = {"cat", "-e", NULL};
	char	split[4][3] = {"cat", "-e", NULL};

	(void)ac;
	(void)av;
	fd_main[0] = dup(STDIN_FILENO);
	fd_main[1] = dup(STDOUT_FILENO);
	fd_main[2] = dup(STDERR_FILENO);
	a = 0;
	while (a < 5)
	{
		pipe(pipe_fd1);
		pipe(pipe_fd2);
		pid[a] = fork();
		if (!pid[a])
		{
			dup2(pipe_fd1[1], STDOUT_FILENO);
			dup2(pipe_fd2[0], STDIN_FILENO);
			close (pipe_fd1[0]);
			close (pipe_fd2[1]);
			execve("/bin/cat", split[a], env);
			exit(0);
		}
		close (pipe_fd1[1]);
		close (pipe_fd2[0]);
		dup2(fd_main[0], STDIN_FILENO);
		dup2(fd_main[1], STDOUT_FILENO);
		dup2(fd_main[2], STDERR_FILENO);
	}
	while (a > 0)
	{
		waitpid(pid[a], 0, 0);
		a--;
	}
	return (0);
}