/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maincwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:41:35 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/21 09:22:56 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mini_test.h"

int	main(void)
{
	char	*str;
	char	*path;

	str = NULL;
	str = getcwd(NULL, 1);
	dprintf(1, "str :%s\n", str);
	free (str);
	path = "bonjour";
	str = getcwd(path, 8);
	dprintf(1, "path :%s\n", str);
	free (str);
	return (0);
}