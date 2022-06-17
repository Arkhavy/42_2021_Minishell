/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:00:00 by ljohnson          #+#    #+#             */
/*   Updated: 2022/06/17 08:10:36 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_set_fd_in(t_cmd *cmd)
{
	if (ft_atoi(cmd->split[0]) != 1)
	{
		if (dup2(ft_atoi(cmd->split[0]), STDIN_FILENO))
			return (mini_error(EBADF));
	}
	return (0);
}

int	mini_set_fd_out(t_cmd *cmd, int slen, int last)
{
	int	redir_len;
	int	fd;

	redir_len = ft_strlen(cmd->split[slen - 1]);
	if (redir_len == 2)
	{
		if (!ft_strncmp(cmd->split[slen - 1], ">&", 2))
			fd = dup(ft_atoi(cmd->split[slen]));
		else
			fd = open(cmd->split[slen], O_WRONLY | O_CREAT | O_APPEND, 0766);
	}
	else
		fd = open(cmd->split[slen], O_WRONLY | O_CREAT | O_TRUNC, 0766);
	if (fd == -1)
		return (mini_error(EBADF) * -1);
	if (last)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (mini_error(EBADF));
	}
	return (0);
}

int	mini_redirect(void)
{
	int		r_index;
	char	c;

	r_index = 1;
	while (r_index)
	{
		r_index = read(STDIN_FILENO, &c, 1);
		if (r_index == -1)
			return (mini_error(EINVAL));
		else if (r_index == 0)
			break ;
		if (write (STDOUT_FILENO, &c, 1) == -1)
			return (mini_error(EPERM));
	}
	return (0);
}

int	mini_redir_hub(t_cmd *cmd, int last)
{
	int	slen;

	slen = ft_splitlen(cmd->split) - 1;
	if (slen == 2)
	{
		if (mini_set_fd_in(cmd))
			return (1);
	}
	if (mini_set_fd_out(cmd, slen, last))
		return (1);
	if (last)
		return (mini_redirect());
	return (0);
}

/*
int	mini_set_fd_in(t_master *master, t_cmd *cmd, int slen)
{
	int	fd_in;

	fd_in = dup(master->fdstruct->fd_link);
	if (slen == 2 && ft_atoi(cmd->split[0]) != 1)
		dup2(ft_atoi(cmd->split[0]), fd_in);
	if (fd_in == -1)
		return (mini_error(EBADF) * -1);
	return (fd_in);
}

int	mini_set_fd_out(t_cmd *cmd, int slen)
{
	int	fd_out;
	int	redir_len;

	fd_out = -1;
	redir_len = ft_get_highest(ft_strlen(cmd->split[slen - 1]), 2);
	if (!ft_strncmp(cmd->split[slen - 1], ">>", redir_len))
		fd_out = open(cmd->split[slen], O_WRONLY | O_CREAT | O_APPEND, 0766);
	else if (!ft_strncmp(cmd->split[slen - 1], ">&", redir_len))
		fd_out = dup(ft_atoi(cmd->split[slen]));
	else
		fd_out = open(cmd->split[slen], O_WRONLY | O_CREAT | O_TRUNC, 0766);
	if (fd_out == -1)
		return (mini_error(EBADF) * -1);
	return (fd_out);
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

int	mini_redir_hub(t_master *master, t_cmd *cmd, int pipe_fd[2], int last)
{
	int	fd_in;
	int	fd_out;
	int	slen;

	slen = ft_splitlen(cmd->split) - 1;
	fd_in = mini_set_fd_in(master, cmd, slen);
	fd_out = mini_set_fd_out(cmd, slen);
	if (fd_in == -1 || fd_out == -1)
		return (1);
	if (!last)
	{
		if (close (pipe_fd[0]))
			return (mini_error(EBADF));
		if (mini_redirect(fd_in, pipe_fd[1]))
			return (1);
	}
	else
	{
		if (mini_redirect(fd_in, fd_out))
			return (1);
		if (close(fd_out) == -1)
			return (mini_error(EBADF));
	}
	if (close(fd_in) == -1)
		return (mini_error(EBADF));
	return (0);
}

int	mini_set_fd_in(int fd_link, t_cmd *cmd, int a)
{
	int	fd_in;

	fd_in = -1;
	if (a == 3)
		fd_in = dup(ft_atoi(cmd->split[0]));
	else
		fd_in = dup(fd_link);
	if (fd_in == -1)
		return (mini_error(EBADF) * -1);
	return (fd_in);
}

int	mini_set_fd_out(t_cmd *cmd, int a)
{
	int	fd_out;

	fd_out = -1;
	if (!ft_strncmp(cmd->split[a - 1], ">>",
			ft_get_highest(ft_strlen(cmd->split[a - 1]), 2)))
		fd_out = open(cmd->split[a], O_WRONLY | O_CREAT | O_APPEND, 0766);
	else if (!ft_strncmp(cmd->split[a - 1], ">&",
			ft_get_highest(ft_strlen(cmd->split[a - 1]), 2)))
		fd_out = dup(ft_atoi(cmd->split[a]));
	else
		fd_out = open(cmd->split[a], O_WRONLY | O_CREAT | O_TRUNC, 0766);
	if (fd_out == -1)
		return (mini_error(EBADF) * -1);
	return (fd_out);
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

int	mini_redirection_hub(t_master *master, t_cmd *cmd)
{
	int	a;
	int	fd_in;
	int	fd_out;

	a = 0;
	while (cmd->split[a])
		a++;
	fd_in = mini_set_fd_in(master->fdstruct->fd_link, cmd, a);
	if (fd_in == -1)
		return (1);
	a--;
	fd_out = mini_set_fd_out(cmd, a);
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

3 parties
p1 = fd_in (facultatif)
p2 = > ou >> ou >&
p3 = fd_out : int if part 2 == >& else fichier

if (p1)
	Split[0] = p1;
	Split[1] = p2;
	Split[2] = p3;
	Split[3] = NULL;
else
	Split[0] = p2;
	Split[1] = p3;
	Split[2] = NULL;

if (p2 == >>)
	p3 = open (file, O_WRONLY | O_CREAT | O_APPEND, 0766)
else if (p2 == >&)
	p3 = dup(ft_atoi(p3))
else
	p3 = open (file, O_WRONLY | O_CREAT | O_TRUNC, 0766)

Split[0] = nombre si il existe sinon > ou >> ou >&
Split[1] = > ou >> ou >& si Split[0] = nombre sinon
c'est fd_out qui peut être un int si >& sinon c'est un nom de fichier
Split[2] = NULL si Split[0] is not digit sinon fd_out
*/