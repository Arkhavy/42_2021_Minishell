/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:49:20 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/28 10:12:44 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_inc/minishell.h"

//Initialise la liste chaînée des variables environnement
int	mini_init_envdata(t_envdata *envdata, char **env)
{
	size_t	a;
	t_env	*env_var;

	a = 0;
	envdata->lst = NULL;
	envdata->lst_size = 0;
	envdata->envmain = env;
	while (env[a])
	{
		env_var = malloc(sizeof(t_env));
		if (!env_var)
			return (mini_errprint(ERR_MALLOC, DFI, DLI, DFU));
		env_var->name = ft_substr(env[a], 0, ft_int_strchr(env[a], '='));
		env_var->value = ft_substr(env[a],
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

//Mémorise les FD de base et le Path de départ pour l'exécution
//Sujet à évolution
int	mini_init_fdstruct(t_fd	*fdstruct, char **env)
{
	size_t	a;

	a = 0;
	fdstruct->fd_in = dup(STDIN_FILENO);
	fdstruct->fd_out = dup(STDOUT_FILENO);
	fdstruct->fd_err = dup(STDERR_FILENO);
	if (fdstruct->fd_in < 0 || fdstruct->fd_out < 0 || fdstruct->fd_err < 0)
		return (mini_errprint(ERR_DUP, DFI, DLI, DFU));
	while (env[a])
	{
		if (!ft_strncmp(env[a], "PWD=", 4))
		{
			fdstruct->startpath = ft_substr(env[a], 4, ft_strlen(env[a]) - 4);
			break ;
		}
		a++;
	}
	if (!env[a])
		fdstruct->startpath = getcwd(NULL, 0);
	if (!fdstruct->startpath)
		return (mini_errprint(ERR_MALLOC, DFI, DLI, DFU));
	return (0);
}
