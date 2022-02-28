/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 09:23:08 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/15 14:19:17 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mini_test.h"

//Récupère les paths environnement pour aller chercher les commandes bash
char	**mini_get_paths(t_pipex pipex)
{
	char	**paths;
	char	*tmp;
	size_t	a;

	a = 0;
	while (ft_strncmp(pipex.env[a], "PATH=", 5))
		a++;
	paths = ft_split(&pipex.env[a][5], ':');
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

//Check chaque env_path avec la commande pour vérifier son existence
char	*mini_get_file(t_pipex pipex, char *cmd)
{
	int		b;
	char	*tmp;
	char	*file;

	b = 0;
	file = NULL;
	while (pipex.env_paths[b])
	{
		tmp = file;
		file = ft_strjoin(pipex.env_paths[b], cmd);
		free (tmp);
		if (!access (file, F_OK))
			break ;
		b++;
	}
	if (access(file, F_OK) == -1)
	{
		free (file);
		mini_print_error(ERR_CMD, FILE, LINE - 3, (char *)FUNC);
		printf("Command input was : %s\n", cmd);
		return (ft_strdup(cmd));
	}
	return (file);
}

//Récupère la commande venant du split et vérifie son existence
char	*mini_get_cmd(t_pipex pipex, char **split, int a)
{
	char	*cmd;
	char	*file;

	if (ft_int_strchr(split[a], ' ') > -1)
		cmd = ft_substr(split[a], 0, ft_int_strchr(split[a], ' '));
	else
		cmd = ft_substr(split[a], 0, ft_strlen(split[a]));
	if (!access(cmd, F_OK))
		return (cmd);
	file = mini_get_file(pipex, cmd);
	free (cmd);
	return (file);
}

void	mini_print_error(char *message, char *file, int line, char *function)
{
	perror(message);
	printf("Error occured in %s at line %d in %s\n", file, line, function);
}
