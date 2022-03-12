/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:04:01 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/12 14:13:58 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

//cd
	//might need pwd
	//change la variable env pwd ?
	//change une variable propre au programme ?
	//chdir is the way to go
	//attention à home et à la tilde ~
	//home est aussi une env_var
	// cd .. cd . cd cd ~ sont donc à surveiller
//la variable pwd dans l'environnement est un problème
//as-t'on réellement besoin du full path avec chdir ?
//j'en fais peut être un peu trop ? peut être pas assez ?
//mini_get_env_var permettra un code modulable sur beaucoup de fonction
	//c'est une fonction qui ira dans un autre fichier à terme
void	*mini_get_env_var(t_envdata *envdata, char *varname)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		if (!ft_strncmp(env_var->name, varname, ft_strlen(varname)))
			return (envdata->lst->content);
		envdata->lst = envdata->lst->next;
	}
	return (NULL);
}

int	mini_change_directory(t_envdata *envdata, char *path)
{
	t_env	*env_var;
	char	*tmp;
	char	*last_path;

	env_var = mini_get_env_var(envdata, "PWD");
	if (!env_var)
		tmp = getcwd(NULL, 0);
	else
		tmp = ft_strdup(env_var->value);
	last_path = ft_strjoin(tmp, "/");
	free (tmp);
	tmp = last_path;
	last_path = ft_strjoin(last_path, path);
	free (tmp);
	if (chdir(last_path) == -1)
		return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
	return (0);
}

int	mini_cd_built_in(t_envdata *envdata, char *path)
{
	t_env	*env_var;

	env_var = NULL;
	if (!path || !path[0])
	{
		env_var = mini_get_env_var(envdata, "HOME");
		if (env_var)
			chdir(env_var->value);
		else
			return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
		return (0);
	}
	else if (path[0] == '~')
	{
		env_var = mini_get_env_var(envdata, "HOME");
		path = ft_strjoin(ft_strdup(env_var->value),
				ft_substr(path, 1, ft_strlen(path)));
		if (chdir(path) == -1)
			return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
		return (0);
	}
	return (mini_change_directory(envdata, path));
}
