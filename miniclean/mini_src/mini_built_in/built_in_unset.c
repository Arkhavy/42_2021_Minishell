/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:29:09 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/17 13:57:37 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_test.h>

int	mini_unset_built_in(t_envdata *envdata, char *varname)
{
	t_env	*env_var;
	void	*previous_link;

	envdata->lst = envdata->start;
	if (!varname || !varname[0])
		return (1);
	if (ft_ischarset('=', varname))
		return (mini_errprint(E_ID, DFI, DLI, DFU));
	env_var = envdata->lst->content;
	previous_link = NULL;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		if (!ft_strncmp(env_var->name, varname, ft_strlen(varname)))
		{
			mini_del_env_var(envdata, previous_link, envdata->lst);
			break ;
		}
		previous_link = envdata->lst;
		envdata->lst = envdata->lst->next;
	}
	return (0);
}
