/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:37:35 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/15 15:42:23 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

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

void	*mini_get_env_var(t_envdata *envdata, char *varname)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		if (!ft_strncmp(env_var->name, varname, ft_strlen(env_var->name)))
			return (envdata->lst->content);
		envdata->lst = envdata->lst->next;
	}
	return (NULL);
}

void	*mini_set_env_var(t_envdata *envdata, char *varname, char *value)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	if (!env_var)
		return (NULL);
	envdata->lst = envdata->start;
	env_var->name = varname;
	env_var->value = value;
	ft_lstadd_back(&envdata->lst, ft_lstnew(env_var));
	envdata->lst_size++;
	return (env_var);
}
