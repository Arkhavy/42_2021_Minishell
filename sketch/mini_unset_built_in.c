/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset_built_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:33:02 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/09 11:29:15 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"
//unset
	//retrait potentiel d'une variable dans la linked list env ?
	//n'importe quelle variable ?
	//peut potentiellement casser l'exécution

//Will be used only if the syntax "unset name" is OK in the parsing
//if !varname -> error code
//if varname is not found, do nothing
//Need to join before and after and delete current link
//Search for the var in the list then deletes it
//Straightforward function for now
//Can break everything if PATH is unset. will need to secure A LOT of things.

int	mini_delete_var(t_list *previous, t_list *current, t_envdata *envdata)
{
	t_env	*env_var;

	env_var = current->content;
	free (env_var->name);
	env_var->name = NULL;
	free (env_var->value);
	env_var->value = NULL;
	previous->next = current->next;
	free (current->content);
	current->content = NULL;
	free (current);
	current = NULL;
	envdata->lst_size--;
	return (0);
}

int	mini_unset_built_in(t_envdata *envdata, char *varname)
{
	t_env	*env_var;
	void	*previous_link;

	envdata->lst = envdata->start;
	if (!varname || !varname[0] || varname[0] == '=')
		return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
	env_var = envdata->lst->content;
	previous_link = NULL;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		if (!ft_strncmp(env_var->name, varname, ft_strlen(varname)))
			return (mini_delete_var(previous_link, envdata->lst, envdata));
		previous_link = envdata->lst;
		envdata->lst = envdata->lst->next;
	}
	return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
}
