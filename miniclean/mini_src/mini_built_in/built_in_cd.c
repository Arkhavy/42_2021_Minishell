/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:29:52 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/20 15:34:37 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_cd_built_in(t_envdata *envdata, char *path)
{
	t_env	*env_var;
	char	*old_pwd;

	env_var = mini_get_env_var(envdata, "HOME");
	old_pwd = getcwd(NULL, 0);
	if (!path || !path[0] || path[0] == '~')
	{
		if (!env_var || chdir(env_var->value) == -1)
		{
			free (old_pwd);
			return (mini_errprint(E_HOME, DFI, DLI, DFU));
		}
	}
	else
	{
		if (chdir(path) == -1)
		{
			free (old_pwd);
			return (mini_errprint(E_CHDIR, DFI, DLI, DFU));
		}
	}
	mini_set_new_value(envdata, "OLDPWD", old_pwd);
	mini_set_new_value(envdata, "PWD", getcwd(NULL, 0));
	return (0);
}
