/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env_minishell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:40:12 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/04 11:42:02 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	display_env_minishell(t_master *master)
{
	t_env	*env_var;
	size_t	a;

	master->envdata->lst = master->envdata->start;
	env_var = NULL;
	a = 0;
	dprintf(1, "\n\n DISPLAY ENV MINISHELL\n\n");
	while (master->envdata->lst)
	{
		env_var = master->envdata->lst->content;
		dprintf(1, "%zu:	%s=%s\n", a, env_var->name, env_var->value);
		master->envdata->lst = master->envdata->lst->next;
		a++;
	}
}
