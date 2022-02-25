/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 10:03:45 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/24 08:32:28 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "oskour.h"

//Affiche les messages d'erreur en ajoutant Perror, fichier, ligne et fonction
int	mini_errprint(char *str, char *file, int line, char *func)
{
	perror(str);
	printf("Error in %s at line %d in %s\n", file, line, func);
	return (1);
}

//Structures initialisées ici seront dans la structure master plus tard
//Le gros de minishell sera dans une autre fonction
//Readline sera juste après les initialisations de structures
int	main(int ac, char **av, char **env)
{
	t_master	master;
	t_envdata	envdata;
	t_fd		fdstruct;

	(void)av;
	if (ac > 1)
		return (mini_errprint(ERR_AC, DFI, DLI, DFU));
	mini_init_envdata(&envdata, env);
	mini_init_fdstruct(&fdstruct, env);
	master.envdata = &envdata;
	master.fdstruct = &fdstruct;
	envdata.lst = envdata.start;
	ft_free_split(envdata.paths);
	mini_free_envlist(&envdata);
	free (fdstruct.startpath);
	return (0);
}
