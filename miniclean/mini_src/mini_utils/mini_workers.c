/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_workers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:51:49 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/20 15:35:34 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
