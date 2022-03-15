/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env_built_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:29:10 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/12 12:42:00 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

//env
	//probably just printing env var from main
	//each line will be stored separately
		//split or linked list ?
			//split might be annoying to modify afterward
			//linked list might be a solution if we add temp env vars
int	mini_env_built_in(t_envdata *envdata, int fd_out)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		ft_dprintf(fd_out, "%s=%s\n", env_var->name, env_var->value);
		envdata->lst = envdata->lst->next;
	}
	return (0);
}
