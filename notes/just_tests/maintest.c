/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:08:13 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/15 14:55:00 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mini_test.h"

char	**create_temp_split(void)
{
	char	**split;

	split = malloc(sizeof(char *) * 10);
	split[0] = ft_strdup("cat");
	split[1] = ft_strdup("grep");
	split[2] = ft_strdup("ls");
	split[3] = ft_strdup("wc");
	split[4] = ft_strdup("tail");
	split[5] = ft_strdup("head");
	split[6] = ft_strdup("sleep");
	split[7] = ft_strdup("touch");
	split[8] = ft_strdup("ouaf");
	split[9] = NULL;
	return (split);
}

int	main(int ac, char **av, char **env)
{
	int		a;
	t_pipex	pipex;

	pipex.env = env;
	pipex.av = av;
	pipex.ac = ac;
	pipex.env_paths = mini_get_paths(pipex);
	a = 0;
	while (pipex.env_paths[a])
	{
		dprintf(1, "env_paths[%d]: %s\n", a, pipex.env_paths[a]);
		a++;
	}
	pipex.cmd_split = create_temp_split();
	a = 0;
	pipex.cmd = NULL;
	while (pipex.cmd_split[a])
	{
		pipex.cmd = mini_get_cmd(pipex, pipex.cmd_split, a);
		dprintf(1, "cmd[%d] = %s\n", a, pipex.cmd);
		free (pipex.cmd);
		a++;
	}
	ft_free_split(pipex.cmd_split);
	ft_free_split(pipex.env_paths);
	return (0);
}
