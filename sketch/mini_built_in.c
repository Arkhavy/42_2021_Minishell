/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:52:51 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/15 15:36:23 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

//env -i ./minishell
	//supprime toutes les variables environnement
	//il faut que ça fonctionne même de cette façon

//< ./minishell > oskour.txt
	//change les fd de départ
	//peut tout casser
	//aled

//pipe et built_in ne font pas bon ménage
	//sauf echo
	//ça implique de vérifier le contenu de chaque commande dans le parsing

/*
unlink after open to avoid fd leaks
unlink permet de "free" un fd une fois que celui-ci est close
par toute les sources qui l'utilisent
 */

/*
Les calls de fonction built-in :
Le parsing se fera avant le lancement des fonctions mini_x_built_in
Le but est d'envoyer seulement les bonnes infos
et donc de trier avant pour ne pas avoir de souci
Cela veut dire les paires de double quotes à faire sauter
les paires de simple quote à faire sauter aussi
parsing à faire sans faute quel que soit le cas
*/