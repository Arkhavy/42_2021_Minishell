/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:04:01 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/16 14:34:55 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

void	mini_add_oldpwd(t_envdata *envdata)
{
	t_env	*current_pwd;
	t_env	*old_pwd;

	current_pwd = mini_get_env_var(envdata, "PWD");
	if (!current_pwd)
		current_pwd = mini_set_env_var(envdata, ft_strdup("PWD"),
				getcwd(NULL, 0));
	old_pwd = mini_get_env_var(envdata, "OLDPWD");
	if (!old_pwd)
		old_pwd = mini_set_env_var(envdata, ft_strdup("OLDPWD"),
				getcwd(NULL, 0));
	else
	{
		free (old_pwd->value);
		old_pwd->value = current_pwd->value;
	}
}

int	mini_change_directory(t_envdata *envdata, char *dest, char *path)
{
	t_env	*env_var;
	char	*newdir;

	env_var = mini_get_env_var(envdata, "PWD");
	newdir = NULL;
	if (!env_var)
		env_var = mini_set_env_var(envdata, ft_strdup("PWD"), getcwd(NULL, 0));
	if (!dest)
	{
		if (path[0] == '/')
			newdir = ft_strfreejoin(env_var->value, path);
		else
		{
			newdir = ft_strfreejoin(env_var->value, ft_strdup("/"));
			newdir = ft_strfreejoin(newdir, path);
		}
		env_var->value = newdir;
		return (chdir(newdir));
	}
	else
	{
		env_var->value = dest;
		return (chdir(dest));
	}
	return (-1);
}

int	mini_cd_built_in(t_envdata *envdata, char *path)
{
	t_env	*env_var;
	char	*destination;

	destination = NULL;
	env_var = mini_get_env_var(envdata, "HOME");
	if (!path || !path[0])
	{
		if (!env_var)
			return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
		destination = ft_strdup(env_var->value);
	}
	else if (path[0] == '~')
	{
		if (!env_var)
			return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
		if (!path[1])
			return (chdir(env_var->value));
		destination = ft_strfreejoin(ft_strdup(env_var->value),
				ft_substr(path, 1, ft_strlen(path)));
		if (!destination)
			return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
	}
	mini_add_oldpwd(envdata);
	return (mini_change_directory(envdata, destination, path));
}
