/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:29:52 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/16 13:11:08 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell_test.h"

//cd
	//home est une env_var
		// if home not set, call l'erreur nous même
	//chdir ne change que la valeur de retour de getcwd
		//on peut utiliser cette valeur pour modifier notre environnement
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
}
