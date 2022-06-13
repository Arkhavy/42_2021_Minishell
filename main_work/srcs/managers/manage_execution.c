/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:07:18 by ljohnson          #+#    #+#             */
/*   Updated: 2022/06/13 09:58:12 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_dup_handler(t_master *master, int pipe_fd[2], int last, int btin)
{
	if (!btin)
		if (close(pipe_fd[0]) == -1)
			return (1);
	if (dup2(master->fdstruct->fd_link, STDIN_FILENO) == -1)
		return (1);
	if (last)
	{
		if (close (pipe_fd[1]) == -1)
			return (1);
		if (dup2(master->fdstruct->fd_out, STDOUT_FILENO) == -1)
			return (1);
	}
	else
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			return (1);
	}
	return (0);
}

int	mini_close_child_process(int pipe_fd, int fd_link)
{
	if (close(pipe_fd) == -1)
		return (1);
	if (close(fd_link) == -1)
		return (1);
	return (0);
}

//Fait tourner chaque path avec la commande pour vérifier son existence
char	*mini_check_cmd_paths(char **paths, char *cmd)
{
	char	*tmp;
	size_t	a;

	a = 0;
	if (!cmd)
		return (NULL);
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	while (paths[a])
	{
		tmp = ft_strjoin(paths[a], cmd);
		if (!access(tmp, F_OK))
			return (tmp);
		free (tmp);
		a++;
	}
	return (NULL);
}
