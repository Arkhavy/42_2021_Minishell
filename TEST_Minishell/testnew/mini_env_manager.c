/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:49:46 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/22 09:24:00 by ljohnson         ###   ########lyon.fr   */
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
		free (env_var->content);
		free (envdata->lst->content);
		tmp = envdata->lst;
		envdata->lst = envdata->lst->next;
		free (tmp);
	}
}

//Initialise la liste chaînée des variables environnement
int	mini_init_envdata(t_envdata *envdata, char **env)
{
	size_t	a;
	t_env	*env_var;

	a = 0;
	envdata->lst = NULL;
	envdata->lst_size = 0;
	while (env[a])
	{
		env_var = malloc(sizeof(t_env));
		if (!env_var)
			return (mini_errprint(ERR_MALLOC, DFI, DLI, DFU));
		env_var->name = ft_substr(env[a], 0, ft_int_strchr(env[a], '='));
		env_var->content = ft_substr(env[a],
				ft_int_strchr(env[a], '=') + 1, ft_strlen(env[a]));
		ft_lstadd_back(&envdata->lst, ft_lstnew(env_var));
		envdata->lst_size++;
		a++;
	}
	envdata->start = envdata->lst;
	envdata->paths = mini_get_paths(env);
	if (!envdata->paths)
		return (mini_errprint(ERR_MALLOC, DFI, DLI, DFU));
	return (0);
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
		ft_putendl_fd(env_var->content, fd_out);
		envdata->lst = envdata->lst->next;
	}
}
