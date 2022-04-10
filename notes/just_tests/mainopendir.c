/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainopendir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:59:47 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/17 13:39:54 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	char	*str;
	DIR		*ouaf;

	(void)ac;
	str = av[1];
	dprintf(1, "str:%s\n", str);
	ouaf = opendir(str);
	ouaf = readdir(ouaf);
	dprintf(1, "str:%s\n", str);
	free (ouaf);
	closedir(ouaf);
	return (0);
}
