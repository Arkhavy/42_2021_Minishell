/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:04:01 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/14 12:52:30 by ljohnson         ###   ########lyon.fr   */
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
	//ajoute une variable OLDPWD non présente au départ du programme
		//doit être récupérée avant exécution
			//quel que soit le cas ou seulement si réussite ?
	//attention aux caractères chelou pouvant faire péter la commande
		//chdir devrait le gérer, mais sait-on jamais
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
		if (!ft_strncmp(env_var->name, varname, ft_strlen(env_var->name)))
			return (envdata->lst->content);
		envdata->lst = envdata->lst->next;
	}
	return (NULL);
}

void	*mini_set_env_var(t_envdata *envdata, char *varname, char *value)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	if (!env_var)
		return (NULL);
	envdata->lst = envdata->start;
	env_var->name = varname;
	env_var->value = value;
	ft_lstadd_back(&envdata->lst, ft_lstnew(env_var));
	envdata->lst_size++;
	return (env_var);
}

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

int	mini_change_directory(t_envdata *envdata, char *destination, char *path)
{
	t_env	*env_var;
	char	*newdir;

	env_var = mini_get_env_var(envdata, "PWD");
	newdir = NULL;
	if (!env_var)
		env_var = mini_set_env_var(envdata, ft_strdup("PWD"), getcwd(NULL, 0));
	if (!destination)
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
		env_var->value = destination;
		return (chdir(destination));
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
