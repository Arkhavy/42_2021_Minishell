/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_chdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:23:56 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/12 13:24:58 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

int	main(void)
{
	dprintf(1, "%d\n", chdir(NULL));
	return (0);
}