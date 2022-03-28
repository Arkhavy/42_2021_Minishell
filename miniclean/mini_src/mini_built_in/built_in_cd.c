/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:29:52 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/28 13:16:28 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_chdir_error(char *err_message, char *old_pwd)
{
	free (old_pwd);
	return (mini_errprint(err_message, DFI, DLI, DFU));
}

int	mini_chdir_home(t_envdata *envdata, char *path, char *old_pwd)
{
	t_env	*env_var;
	char	*new_pwd;

	new_pwd = NULL;
	env_var = mini_get_env_var(envdata, "HOME");
	if (!env_var)
		return (mini_chdir_error(E_HOME, old_pwd));
	if (path[1] == '/')
		new_pwd = ft_strfreejoin(ft_strdup(env_var->value),
				ft_substr(path, 1, ft_strlen(path)));
	else
		new_pwd = ft_strdup(env_var->value);
	if (chdir(new_pwd) == -1)
	{
		free (new_pwd);
		return (mini_chdir_error(E_CHDIR, old_pwd));
	}
	free (new_pwd);
	return (0);
}

int	mini_cd_built_in(t_envdata *envdata, char *path)
{
	t_env	*env_var;
	char	*old_pwd;

	env_var = NULL;
	old_pwd = getcwd(NULL, 0);
	if (!path || !path[0] || path[0] == '~')
		if (mini_chdir_home(envdata, path, old_pwd))
			return (1);
	if (path[0] == '-' && !path[1])
	{
		env_var = mini_get_env_var(envdata, "OLDPWD");
		if (!env_var || !env_var->value)
			return (mini_chdir_error(E_CHDIR, old_pwd));
		if (chdir(env_var->value) == -1)
			return (mini_chdir_error(E_CHDIR, old_pwd));
	}
	else
		if (chdir(path) == -1)
			return (mini_chdir_error(E_CHDIR, old_pwd));
	mini_set_new_value(envdata, "OLDPWD", old_pwd);
	mini_set_new_value(envdata, "PWD", getcwd(NULL, 0));
	return (0);
}
