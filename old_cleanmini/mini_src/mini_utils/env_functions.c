/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:56:51 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/31 15:31:46 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Functions needed
	//Check if env_var is valid (POSIX norm for var names)
	//Does init has to check if the var already exist ?
		//That's an annoying one but needed
	//Expand : aller chercher une env_var si $ est trouvé dans le parsing
		//rajouter le contenu de la variable à la place de son nom
		//remalloc incoming oskour
//Vérifier les retours d'erreur et les conditions d'arrêt des fonctions
//Probable réécriture entière du projet au propre, ça devient le bordel
int	mini_remove_env_var_value(t_envdata *envdata, char *name)
{
	t_env	*env_var;

	env_var = mini_get_env_var_by_name(envdata, name);
	if (!env_var)
		return (mini_errprint(E_VAR, DFI, DLI, DFU));
	free (env_var->value);
	env_var->value = NULL;
	return (0);
}
