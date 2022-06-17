/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:45:00 by ljohnson          #+#    #+#             */
/*   Updated: 2022/06/17 10:56:35 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_env_built_in(t_envdata *envdata, t_cmd *cmd)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	env_var = NULL;
	if (cmd->split[1])
		return (mini_error(ENOENT));
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		if (env_var && env_var->value)
			ft_dprintf(STDOUT_FILENO, "%s=%s\n", env_var->name, env_var->value);
		envdata->lst = envdata->lst->next;
	}
	return (0);
}
