/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:12:18 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/20 15:35:25 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_free_envlist(t_envdata *envdata)
{
	t_env	*env_var;
	void	*tmp;

	envdata->lst = envdata->start;
	env_var = NULL;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		free (env_var->name);
		free (env_var->value);
		free (envdata->lst->content);
		tmp = envdata->lst;
		envdata->lst = envdata->lst->next;
		free (tmp);
	}
}

void	mini_del_env_var(t_envdata *envdata, t_list *prev, t_list *current)
{
	t_env	*env_var;

	env_var = current->content;
	if (env_var->name)
	{
		free(env_var->name);
		env_var->name = NULL;
	}
	if (env_var->value)
	{
		free(env_var->value);
		env_var->value = NULL;
	}
	prev->next = current->next;
	if (current->content)
	{
		free(current->content);
		current->content = NULL;
	}
	if (current)
	{
		free(current);
		current = NULL;
	}
	envdata->lst_size--;
}

void	mini_set_new_value(t_envdata *envdata, char *varname, char *value)
{
	t_env	*env_var;

	env_var = mini_get_env_var(envdata, varname);
	if (!env_var)
		env_var = mini_set_env_var(envdata, varname, value);
	else
	{
		free (env_var->value);
		env_var->value = ft_strdup(value);
	}
	free (value);
}

void	*mini_get_env_var(t_envdata *envdata, char *varname)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		if (!ft_strncmp(env_var->name, varname, ft_strlen(varname)))
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
	env_var->name = ft_strdup(varname);
	env_var->value = ft_strdup(value);
	ft_lstadd_back(&envdata->lst, ft_lstnew(env_var));
	envdata->lst_size++;
	return (env_var);
}
