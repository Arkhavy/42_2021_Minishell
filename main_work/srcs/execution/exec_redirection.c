/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:00:00 by ljohnson          #+#    #+#             */
/*   Updated: 2022/06/16 16:05:03 by ljohnson         ###   ########lyon.fr   */
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
