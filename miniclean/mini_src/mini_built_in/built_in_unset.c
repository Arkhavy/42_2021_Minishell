/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:29:09 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/29 14:06:12 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_check_varname(char *varname)
{
	size_t	a;

	a = 0;
	if ((varname[0] < 'A' || (varname[0] > 'Z' && varname[0] < 'a')
			|| varname[0] > 'z') && varname[0] != '_')
		return (1);
	while (varname[a])
	{
		if (varname[a] < '0' || (varname[a] > '9' && varname[a] < 'A')
			|| (varname[a] > 'Z' && varname[a] < '_')
			|| (varname[a] > '_' && varname[a] < 'a') || varname[a] > 'z')
			return (1);
		a++;
	}
	return (0);
}

int	mini_unset_built_in(t_envdata *envdata, char *varname)
{
	t_env	*env_var;
	void	*previous_link;
	size_t	varname_len;

	envdata->lst = envdata->start;
	if (!varname || !varname[0])
		return (1);
	if (mini_check_varname(varname))
		return (mini_errprint(E_ID, DFI, DLI, DFU));
	env_var = NULL;
	previous_link = NULL;
	varname_len = ft_strlen(varname);
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		if (!ft_strncmp(env_var->name, varname,
				ft_get_highest(varname_len, ft_strlen(env_var->name))))
		{
			mini_del_env_var(envdata, previous_link, envdata->lst);
			break ;
		}
		previous_link = envdata->lst;
		envdata->lst = envdata->lst->next;
	}
	return (0);
}
