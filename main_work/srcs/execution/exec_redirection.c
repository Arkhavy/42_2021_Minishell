/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:16:13 by ljohnson          #+#    #+#             */
/*   Updated: 2022/06/10 14:07:16 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_set_fd_in(t_cmd *cmd, int a)
{
	int	fd_in;

	fd_in = -1;
	if (a == 3)
		fd_in = dup(ft_atoi(cmd->split[0]));
	else
		fd_in = dup(STDOUT_FILENO);
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

int	mini_redirection_hub(t_cmd *cmd)
{
	int	a;
	int	fd_in;
	int	fd_out;

	a = 0;
	while (cmd->split[a])
		a++;
	fd_in = mini_set_fd_in(cmd, a);
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

/*
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
