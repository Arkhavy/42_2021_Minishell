/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_chdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:23:56 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/16 10:17:06 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

int	main(void)
{
	int	fd;

	fd = open("outfile.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	dprintf(1, "getcwd before: %s\n", getcwd(NULL, 0));
	chdir("../..");
	dprintf(fd, "getcwd after: %s\n", getcwd(NULL, 0));
	close (fd);
	return (0);
}
