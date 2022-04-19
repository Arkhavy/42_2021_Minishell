/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envdata_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:34:38 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/31 10:39:46 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*mini_get_env_var_by_index(t_envdata *envdata, int index)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		if (env_var->index == index)
			return (env_var);
		envdata->lst = envdata->lst->next;
	}
	return (NULL);
}

void	mini_reset_env_list_index(t_envdata *envdata)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		env_var->index = -1;
		envdata->lst = envdata->lst->next;
	}
}

void	mini_set_env_list_index(t_envdata *envdata)
{
	t_env	*env_var;
	t_env	*cmp_var;
	size_t	count;
	int		highest_len;

	count = 0;
	highest_len = 0;
	while (count < envdata->lst_size)
	{
		env_var = mini_get_env_var_by_index(envdata, -1);
		if (!env_var)
			break ;
		env_var->index = 0;
		envdata->lst = envdata->start;
		while (envdata->lst)
		{
			cmp_var = envdata->lst->content;
			highest_len = ft_get_highest(env_var->name_len, cmp_var->name_len);
			if (ft_strncmp(env_var->name, cmp_var->name, highest_len) > 0)
				env_var->index++;
			envdata->lst = envdata->lst->next;
		}
		count++;
	}
}
