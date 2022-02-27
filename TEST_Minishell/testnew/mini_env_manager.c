/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:49:46 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/27 16:27:24 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "oskour.h"

//Permet de free l'intégralité de la liste chaînée des variables environnement
void	mini_free_envlist(t_envdata *envdata)
{
	t_env	*env_var;
	void	*tmp;

	envdata->lst = envdata->start;
	env_var = NULL;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		free (env_var->name);
		free (env_var->value);
		free (envdata->lst->content);
		tmp = envdata->lst;
		envdata->lst = envdata->lst->next;
		free (tmp);
	}
}

//Récupère les paths environnement pour aller chercher les commandes bash
char	**mini_get_paths(char **env)
{
	char	**paths;
	char	*tmp;
	size_t	a;

	a = 0;
	while (ft_strncmp(env[a], "PATH=", 5))
		a++;
	paths = ft_split(&env[a][5], ':');
	if (!paths)
		return (NULL);
	a = 0;
	while (paths[a])
	{
		tmp = paths[a];
		paths[a] = ft_strjoin(paths[a], "/");
		free (tmp);
		a++;
	}
	return (paths);
}

//Built-in de la commande env
//Sujet à changement
void	mini_bi_env(t_envdata *envdata, int fd_out)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		ft_putstr_fd(env_var->name, fd_out);
		ft_putchar_fd('=', fd_out);
		ft_putendl_fd(env_var->value, fd_out);
		envdata->lst = envdata->lst->next;
	}
}
