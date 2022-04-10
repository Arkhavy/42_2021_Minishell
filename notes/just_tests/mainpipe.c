/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:51:36 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/18 18:04:40 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int	pipe_fd[2];

	pipe(pipe_fd);
	dup2(pipe_fd[0], STDOUT);
	dup2(pipe_fd[1], STDIN);
	access(path, F_OK);
	execve();
	return (pipe_fd[0]);
	return (0);
}

fd_main = fonction();