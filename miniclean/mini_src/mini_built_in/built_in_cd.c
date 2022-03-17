/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:29:52 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/17 13:56:55 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_test.h>

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

// oid	mini_add_oldpwd(t_envdata *envdata)
// {
// 	t_env	*current_pwd;
// 	t_env	*old_pwd;

// 	current_pwd = mini_get_env_var(envdata, "PWD");
// 	if (!current_pwd)
// 		current_pwd = mini_set_env_var(envdata, ft_strdup("PWD"),
// 				getcwd(NULL, 0));
// 	old_pwd = mini_get_env_var(envdata, "OLDPWD");
// 	if (!old_pwd)
// 		old_pwd = mini_set_env_var(envdata, ft_strdup("OLDPWD"),
// 				getcwd(NULL, 0));
// 	else
// 	{
// 		free (old_pwd->value);
// 		old_pwd->value = current_pwd->value;
// 	}
// }

// int	mini_change_directory(t_envdata *envdata, char *dest, char *path)
// {
// 	t_env	*env_var;
// 	char	*newdir;

// 	env_var = mini_get_env_var(envdata, "PWD");
// 	newdir = NULL;
// 	if (!env_var)
// 		env_var = mini_set_env_var(envdata, ft_strdup("PWD"), getcwd(NULL, 0));
// 	if (!dest)
// 	{
// 		if (path[0] == '/')
// 			newdir = ft_strfreejoin(env_var->value, path);
// 		else
// 		{
// 			newdir = ft_strfreejoin(env_var->value, ft_strdup("/"));
// 			newdir = ft_strfreejoin(newdir, path);
// 		}
// 		env_var->value = newdir;
// 		return (chdir(newdir));
// 	}
// 	else
// 	{
// 		env_var->value = dest;
// 		return (chdir(dest));
// 	}
// 	return (-1);
// }

// int	mini_cd_built_in(t_envdata *envdata, char *path)
// {
// 	t_env	*env_var;
// 	char	*destination;

// 	destination = NULL;
// 	env_var = mini_get_env_var(envdata, "HOME");
// 	if (!path || !path[0])
// 	{
// 		if (!env_var)
// 			return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
// 		destination = ft_strdup(env_var->value);
// 	}
// 	else if (path[0] == '~')
// 	{
// 		if (!env_var)
// 			return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
// 		if (!path[1])
// 			return (chdir(env_var->value));
// 		destination = ft_strfreejoin(ft_strdup(env_var->value),
// 				ft_substr(path, 1, ft_strlen(path)));
// 		if (!destination)
// 			return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
// 	}
// 	mini_add_oldpwd(envdata);
// 	return (mini_change_directory(envdata, destination, path));
// }
