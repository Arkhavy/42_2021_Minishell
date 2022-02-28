/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:50:30 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/28 10:14:45 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

//Built-in de la commande pwd
//Sujet à changement
int	mini_bi_pwd(int fd_out)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
		return (mini_errprint(ERR_CWD, DFI, DLI, DFU));
	ft_putendl_fd(str, fd_out);
	free (str);
	return (0);
}
