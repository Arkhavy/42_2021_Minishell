/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:15:26 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/31 10:28:18 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_free_envdata_list(t_envdata *envdata)
{
	t_env	*env_var;
	void	*tmp;

	envdata->lst = envdata->start;
	env_var = NULL;
	tmp = NULL;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		free (env_var->name);
		env_var->name = NULL;
		free (env_var->value);
		env_var->value = NULL;
		env_var->name_len = 0;
		env_var->index = 0;
		free (envdata->lst->content);
		envdata->lst->content = NULL;
		tmp = envdata->lst;
		envdata->lst = envdata->lst->next;
		free (tmp);
		tmp = NULL;
	}
}

void	mini_end_of_program(t_master *master)
{
	master->envdata->lst = master->envdata->start;
	if (master->envdata)
	{
		if (master->envdata->lst)
			mini_free_envdata_list(master->envdata);
		if (master->envdata->paths)
			ft_free_split(master->envdata->paths);
		free (master->envdata);
		master->envdata = NULL;
	}
}
