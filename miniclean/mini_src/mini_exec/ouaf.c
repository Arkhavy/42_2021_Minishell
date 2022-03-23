/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ouaf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:04:02 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/23 16:40:08 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**mini_add_slash(char **paths)
{
	char	*tmp;
	size_t	a;

	a = 0;
	tmp = NULL;
	while (paths[a])
	{
		tmp = paths[a];
		paths[a] = ft_strjoin(paths[a], "/");
		free (tmp);
		a++;
	}
	return (paths);
}

char	*mini_check_cmd(char *raw_cmd, char **paths)
{
	size_t	a;
	char	*cmd;

	a = 0;
	if (ft_int_strchr(raw_cmd, ' ') == -1)
		cmd = ft_strdup(raw_cmd);
	else
		cmd = ft_substr(raw_cmd, 0, ft_int_strchr(raw_cmd, ' '));
	if (!access(cmd, F_OK))
		return (cmd);
	while (paths[a])
	{
		cmd = ft_strfreejoin(ft_strdup(paths[a]), cmd);
		if (!access(cmd, F_OK))
			return (cmd);
		a++;
	}
	free (cmd);
	return (NULL);
}

char	*mini_get_cmd(t_envdata *envdata, char *raw_cmd)
{
	t_env	*env_var;
	char	*cmd;
	char	**paths;

	cmd = NULL;
	paths = NULL;
	env_var = mini_get_env_var(envdata, "PATH");
	if (!env_var || !env_var->value)
	{
		mini_errprint(E_PATH, DFI, DLI, DFU);
		return (NULL);
	}
	paths = mini_add_slash(ft_split(env_var->value, ':'));
	if (!paths)
	{
		mini_errprint(E_MALLOC, DFI, DLI, DFU);
		return (NULL);
	}
	cmd = mini_check_cmd(raw_cmd, paths);
	ft_free_split(paths);
	return (cmd);
}

//prototype might change
int	mini_cmd_handler(t_envdata *envdata, char *raw_cmd, int fd_in, int fd_out)
{
	char	**env_split;
	char	**cmd_split;
	char	*cmd;

	env_split = NULL;
	cmd_split = NULL;
	cmd = mini_get_cmd(envdata, raw_cmd);
	if (cmd)
	{
		cmd_split = ft_split(raw_cmd, ' ');
		if (access(cmd, X_OK) == -1)
			return (mini_errprint(E_ACCESS_X, DFI, DLI, DFU));
		env_split = mini_linked_to_split(envdata->lst, envdata->lst_size);
		if (execve(cmd, cmd_split, env_split) == -1)
			return (mini_errprint(E_EXECVE, DFI, DLI, DFU));
		ft_free_split(env_split);
		ft_free_split(cmd_split);
		free (cmd);
		return (fd_out);
	}
	free (cmd);
	return (-1);
}

/*
exec
pipex

fd_in
fd_out
(<command> [option] [arg]) = one char *
env needed for execve
path needed for command
if path not set
	getenv ?
	or error and don't work ?
	does getenv(PATH) works even when the var is unset ?
	is it ok to set paths by hand if not set ? (not sure about this one)
	relative paths will not work, absolute paths 
	will work anyway unless access is denied
else
	pipex_bonus work


get_path -> ce sera un check depuis la liste chaînée,
pas de problème concernant strncmp vu qu'il ne sera pas utilisé
split des paths de toute façon juste après
	
	env_var = mini_get_env_var(envdata, "PATH");
	if (!env_var)
		mini_errprint(E_PATH, DFI, DLI, DFU); //error : path not set ?
	else
	paths = ft_split(env_var->value, ':');
	if (!check_cmd(cmd, paths))
		access(X_OK)
		env_split = mini_linked_to_split(envdata->lst);
		execve(cmd, paths, env_split);
	else
		mini_errprint(E_CMD, DFI, DLI, DFU); //error : command not found
		exit child
*/