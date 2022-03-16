/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:15:28 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/16 14:24:09 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

// int	mini_init_envdata(t_envdata *envdata, char **env)
// {
// 	size_t	a;
// 	t_env	*env_var;

// 	a = 0;
// 	envdata->lst = NULL;
// 	envdata->lst_size = 0;
// 	envdata->envmain = env;
// 	while (env[a])
// 	{
// 		env_var = malloc(sizeof(t_env));
// 		if (!env_var)
// 			return (mini_errprint(ERR_MALLOC, DFI, DLI, DFU));
// 		env_var->name = ft_substr(env[a], 0, ft_int_strchr(env[a], '='));
// 		env_var->value = ft_substr(env[a],
// 				ft_int_strchr(env[a], '=') + 1, ft_strlen(env[a]));
// 		ft_lstadd_back(&envdata->lst, ft_lstnew(env_var));
// 		envdata->lst_size++;
// 		a++;
// 	}
// 	envdata->start = envdata->lst;
// 	envdata->paths = mini_get_paths(env);
// 	if (!envdata->paths)
// 		return (mini_errprint(ERR_MALLOC, DFI, DLI, DFU));
// 	return (0);
// }

// int	mini_init_fdstruct(t_fd	*fdstruct, char **env)
// {
// 	size_t	a;

// 	a = 0;
// 	fdstruct->fd_in = dup(STDIN_FILENO);
// 	fdstruct->fd_out = dup(STDOUT_FILENO);
// 	fdstruct->fd_err = dup(STDERR_FILENO);
// 	if (fdstruct->fd_in < 0 || fdstruct->fd_out < 0 || fdstruct->fd_err < 0)
// 		return (mini_errprint(ERR_DUP, DFI, DLI, DFU));
// 	while (env[a])
// 	{
// 		if (!ft_strncmp(env[a], "PWD=", 4))
// 		{
// 			fdstruct->startpath = ft_substr(env[a], 4, ft_strlen(env[a]) - 4);
// 			break ;
// 		}
// 		a++;
// 	}
// 	if (!env[a])
// 		fdstruct->startpath = getcwd(NULL, 0);
// 	if (!fdstruct->startpath)
// 		return (mini_errprint(ERR_MALLOC, DFI, DLI, DFU));
// 	return (0);
// }

// void	mini_free_envlist(t_envdata *envdata)
// {
// 	t_env	*env_var;
// 	void	*tmp;

// 	envdata->lst = envdata->start;
// 	env_var = NULL;
// 	while (envdata->lst)
// 	{
// 		env_var = envdata->lst->content;
// 		free (env_var->name);
// 		free (env_var->value);
// 		free (envdata->lst->content);
// 		tmp = envdata->lst;
// 		envdata->lst = envdata->lst->next;
// 		free (tmp);
// 	}
// }

char	**mini_get_paths(char **env)
{
	char	**paths;
	char	*tmp;
	size_t	a;

	a = 0;
	while (env[a] && ft_strncmp(env[a], "PATH=", 5))
		a++;
	if (env[a])
		paths = ft_split(&env[a][5], ':');
	else
		return (NULL);
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

char	**mini_linked_to_split(t_list *lst, size_t lst_size)
{
	t_env	*link;
	char	**split;
	char	*tmp;
	size_t	a;

	a = 0;
	split = malloc(sizeof(char *) * (lst_size + 1));
	if (!split)
		return (NULL);
	while (a < lst_size && lst)
	{
		link = lst->content;
		split[a] = ft_strjoin(link->name, "=");
		tmp = split[a];
		split[a] = ft_strjoin(split[a], link->value);
		free (tmp);
		lst = lst->next;
		a++;
	}
	split[a] = NULL;
	return (split);
}

// void	mini_end_of_program(t_master *master)
// {
// 	master->envdata->lst = master->envdata->start;
// 	if (master->envdata->paths)
// 		ft_free_split (master->envdata->paths);
// 	if (master->envdata)
// 		mini_free_envlist (master->envdata);
// 	if (master->fdstruct->startpath)
// 		free (master->fdstruct->startpath);
// 	close (master->fdstruct->fd_in);
// 	close (master->fdstruct->fd_out);
// 	close (master->fdstruct->fd_err);
// }

/**
 * Fonctions à test
 * mini_bi_unset (mini_built_in.c)
 * mini_bi_env (mini_env_manager.c)
 * Ouaf.
*/