/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:16:13 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/08 10:26:10 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_set_fd_in(t_cmd *cmd, int *i)
{
	int	fd_in;

	if (ft_isdigit(cmd->raw[0]))
	{
		fd_in = dup(ft_atoi(cmd->split[0]));
		if (fd_in == -1)
			return (mini_error(EBADF) * -1);
	}
	else
	{
		*i = 0;
		fd_in = dup(STDOUT_FILENO);
		if (fd_in == -1)
			return (mini_error(EBADF) * -1);
	}
	return (fd_in);
}

int	mini_set_fd_out(t_cmd *cmd, int i)
{
	int	fd;

	fd = -1;
	if (cmd->raw[i] == '>' && cmd->raw[i + 1] == '>')
	{
		fd = open(cmd->split[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (mini_error(EINVAL) * -1);
	}
	else if (cmd->raw[i] == '>' && cmd->raw[i + 1] != '>')
	{
		if (cmd->raw[i + 1] == '&' && ft_isdigit(cmd->raw[i + 2]))
		{
			fd = dup(ft_atoi(cmd->split[i + 1]));
			if (fd == -1)
				return (mini_error(EBADF) * -1);
		}
		else
		{
			fd = open(cmd->split[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (mini_error(EINVAL) * -1);
		}
	}
	return (fd);
}

int	mini_redirect(int fd_in, int fd_out)
{
	int		r_index;
	char	c;

	r_index = 1;
	while (r_index)
	{
		r_index = read(fd_in, &c, 1);
		if (r_index == -1)
			return (mini_error(EINVAL));
		else if (r_index == 0)
			break ;
		if (write (fd_out, &c, 1) == -1)
			return (mini_error(EPERM));
	}
	return (0);
}

int	mini_redirection_hub(t_cmd *cmd)
{
	int		i;
	int		fd_in;
	int		fd_out;

	i = 1;
	fd_in = mini_set_fd_in(cmd, &i);
	if (fd_in == -1)
		return (1);
	fd_out = mini_set_fd_out(cmd, i);
	if (fd_out == -1)
		return (1);
	if (mini_redirect(fd_in, fd_out))
		return (1);
	if (close (fd_in) == -1)
		return (mini_error(EBADF));
	if (close (fd_out) == -1)
		return (mini_error(EBADF));
	return (0);
}

//redirection from a particular fd, valid or not
//redirection from STDOUT_FILENO / fd_link, last output of command
//open outfile in append mode
//if only one >
//write on a particular fd in trunc mode
//open outfile in trunc mode