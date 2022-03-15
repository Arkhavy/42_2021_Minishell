/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo_built_in.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:52:40 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/11 09:20:58 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

//echo
	//option n
	//affiche logiquement l'argument donné derrière
	//fonctionne avec les pipes ?
	//fonctionne avec les redirections ?
//echo
//has an option, -n -> will be a boolean
//print the arg behind it
	// if !arg, print \n
	// if -n, no \n at the end, else add \n

//Potentiel changement sur le traitement de l'option
	//Recevoir seulement echo -n <arg> en un seul char* ?
	//checker nous même l'existence du -n ?
		//c'est une option envisageable
		//cf en dessous

int	mini_echo_built_in(char *arg, int option, int fd_out)
{
	if (!option)
		ft_dprintf(fd_out, "%s\n", arg);
	else
		ft_dprintf(fd_out, "%s", arg);
	return (0);
}
