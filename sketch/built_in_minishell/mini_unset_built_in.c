/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset_built_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:33:02 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/16 14:39:36 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

int	mini_unset_built_in(t_envdata *envdata, char *varname)
{
	t_env	*env_var;
	void	*previous_link;

	envdata->lst = envdata->start;
	if (!varname || !varname[0] || ft_ischarset('=', varname))
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
