/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:52:51 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/22 08:25:47 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo
	//option n
//pwd
//cd
	//might need pwd
//export
//unset
//env
	//probably just printing env var from main
	//each line will be stored separately
		//split or linked list ?
			//split might be annoying to modify afterward
			//linked list might be a solution if we add temp env vars
//exit

/*
unlink after open to avoid fd leaks
unlink permet de "free" un fd une fois que celui-ci est close
par toute les sources qui l'utilisent
 */