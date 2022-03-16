/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_notes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:40:21 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/16 14:41:04 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*export
	//ajout potentiel d'une variable dans la linked list env
	//où dans cette liste ? fin ? début ? milieu ??

	//IT WORKS
	//Will be used only if the syntax "export NAME=value" is OK in the parsing
	//newvar = "NAME=value"
	//ATTENTION = Les doubles quotes doivent être retirées
	 * #CAS RELOUS :
	 * export ARG=value
	 * export "ARG"=value
	 * export ARG="value"
	 * export "ARG"="value"
	 * export ""ARG"="value""
	 * value = NULL
	 * export ARG+=value when ARG doesn't exist -> it works too lol
	 * if newvar doesn't respect "NAME=value" syntax, don't do anything
	 * if +=, we need to append to the ned of value if NAME is found
	 * trim_quote servira à régler ces soucis (parsing)

	//Fonctionne, mais besoin d'un parsing solide avant ou pendant la fonction
	//les quotes autour de l'ensemble de l'arg seront gérées avant la fonction
	//les quotes autour de name et value seront gérées pendant leur ajout
		//après leur substr
		//avant le checkname
		//avant leur ajout dans la linked lst
	//ft_strtrim fera le boulot très efficacement

	//VA AVOIR BESOIN D'UNE REFONTE AVEC DES MODULES
*/

/*cd
	//home est une env_var
		// if home not set, call l'erreur nous même
	//chdir ne change que la valeur de retour de getcwd
		//on peut utiliser cette valeur pour modifier notre environnement
	//might need pwd
	//change la variable env pwd ?
	//change une variable propre au programme ?
	//chdir is the way to go
	//attention à home et à la tilde ~
	//home est aussi une env_var
	// cd .. cd . cd cd ~ sont donc à surveiller
	//ajoute une variable OLDPWD non présente au départ du programme
		//doit être récupérée avant exécution
			//quel que soit le cas ou seulement si réussite ?
	//attention aux caractères chelou pouvant faire péter la commande
		//chdir devrait le gérer, mais sait-on jamais
//la variable pwd dans l'environnement est un problème
//as-t'on réellement besoin du full path avec chdir ?
//j'en fais peut être un peu trop ? peut être pas assez ?
//mini_get_env_var permettra un code modulable sur beaucoup de fonction
	//c'est une fonction qui ira dans un autre fichier à terme
*/

/*echo
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
*/

/*env
	//probably just printing env var from main
	//each line will be stored separately
		//split or linked list ?
			//split might be annoying to modify afterward
			//linked list might be a solution if we add temp env vars
*/

/*exit
	//que doit-on faire exactement ?
	//full return ?
	//full exit ?
	//fin de minishell ?
	//fin du heredoc seulement si on est dedans ?
	//ne pas oublier le code erreur errno (g_var ?)
	//attention aux pipe
*/

/*pwd
//Should be working
//Still thinking about weird cases
	//affichage path working directory
		//variable env pwd
		//if does not exist, getcwd
*/

/*unset
	//retrait potentiel d'une variable dans la linked list env ?
	//n'importe quelle variable ?
	//peut potentiellement casser l'exécution

//Will be used only if the syntax "unset name" is OK in the parsing
 *
 * if NULL -> does nothing
 * if found -> delete and says nothing
 * if not found -> does nothing
 * if '=' is found in str -> bash: unset: '<arg>': not a valid identifier

//Need to join before and after and delete current link
//Search for the var in the list then deletes it
//Can break everything if PATH is unset. will need to secure A LOT of things.
*/

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