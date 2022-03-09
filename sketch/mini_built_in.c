/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:52:51 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/07 18:52:19 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

//pwd
	//affichage path working directory
		//variable env pwd ?
		//commande getcwd ?
			//laquelle est la plus intéressante ?
//cd
	//might need pwd
	//change la variable env pwd ?
	//change une variable propre au programme ?

//env
	//probably just printing env var from main
	//each line will be stored separately
		//split or linked list ?
			//split might be annoying to modify afterward
			//linked list might be a solution if we add temp env vars
//exit
	//que doit-on faire exactement ?
	//full return ?
	//full exit ?
	//fin de minishell ?
	//fin du heredoc seulement si on est dedans ?

/*
unlink after open to avoid fd leaks
unlink permet de "free" un fd une fois que celui-ci est close
par toute les sources qui l'utilisent
 */
