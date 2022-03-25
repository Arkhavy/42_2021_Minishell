/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_workers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:51:49 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/25 07:55:04 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_is_builtin(char *raw_cmd)
{
	if (!ft_strncmp(raw_cmd, "echo", ft_strlen("echo")))
		return (1);
	else if (!ft_strncmp(raw_cmd, "cd", ft_strlen("cd")))
		return (2);
	else if (!ft_strncmp(raw_cmd, "env", ft_strlen("env")))
		return (3);
	else if (!ft_strncmp(raw_cmd, "exit", ft_strlen("exit")))
		return (4);
	else if (!ft_strncmp(raw_cmd, "export", ft_strlen("export")))
		return (5);
	else if (!ft_strncmp(raw_cmd, "pwd", ft_strlen("pwd")))
		return (6);
	else if (!ft_strncmp(raw_cmd, "unset", ft_strlen("unset")))
		return (7);
	return (0);
}

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
