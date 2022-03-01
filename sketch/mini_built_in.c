/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:52:51 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/28 13:57:37 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

//echo
	//option n
	//affiche logiquement l'argument donné derrière
	//fonctionne avec les pipes ?
	//fonctionne avec les redirections ?
//pwd
	//affichage path working directory
		//variable env pwd ?
		//commande getcwd ?
			//laquelle est la plus intéressante ?
//cd
	//might need pwd
	//change la variable env pwd ?
	//change une variable propre au programme ?
//export
	//ajout potentiel d'une variable dans la linked list env
	//où dans cette liste ? fin ? début ? milieu ??
//unset
	//retrait potentiel d'une variable dans la linked list env ?
	//n'importe quelle variable ?
	//peut potentiellement casser l'exécution
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

//Should remove an entire link of the linked list ?
//Or does it only clean the link without removing it ?
//Will be used only if the syntax "unset name" is OK in the parsing
int	mini_bi_unset(t_envdata *envdata, char *varname)
{
	size_t	a;
	t_env	*env_var;
	size_t	len;

	envdata->lst = envdata->start;
	a = 0;
	len = ft_strlen(varname);
	env_var = envdata->lst->content;
	while (ft_strncmp(env_var->name, varname, len) != 0 && envdata->lst)
	{
		env_var = envdata->lst->content;
		envdata->lst = envdata->lst->next;
	}
	if (!envdata->lst)
		return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
	else
	{
		ft_free (&env_var->name);
		ft_free (&env_var->value);
		free (env_var);
	}
}

//Will be used only if the syntax "export name=value" is OK in the parsing
//newvar = "name=value"
int	mini_bi_export(t_envdata *envdata, char *newvar)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	if (!newvar || !newvar[0])
		return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
	env_var = malloc(sizeof(t_env));
	if (!env_var)
		return (mini_errprint(ERR_MALLOC, DFI, DLI, DFU));
	env_var->name = ft_substr(newvar, 0, ft_int_strchr(newvar, '='));
	env_var->value = ft_substr(newvar,
			ft_int_strchr(newvar, '=') + 1, ft_strlen(newvar));
	ft_lstadd_back(&envdata->lst, ft_lstnew(env_var));
	envdata->lst_size++;
	return (0);
}
