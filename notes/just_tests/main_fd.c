/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 10:30:54 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/16 11:04:59 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	a;

	a = 0;
	while (str[a])
		a++;
	return (a);
}

int	main(void)
{
	int		fd_file;
	int		fd_out;
	char	*str = "ouaf\n";

	fd_out = dup(STDOUT_FILENO);
	fd_file = open("file.txt", O_RDWR);
	dup2(fd_file, STDOUT_FILENO);
	write (1, str, ft_strlen(str));
	dup2(fd_out, STDOUT_FILENO);
	write (1, str, ft_strlen(str));
	close (fd_file);
	close (fd_out);
	return (0);
}
