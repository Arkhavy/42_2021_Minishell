/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:58:11 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/26 10:33:05 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_end_of_program(t_master *master)
{
	master->envdata->lst = master->envdata->start;
	if (master->envdata->paths)
		ft_free_split (master->envdata->paths);
	if (master->envdata->lst)
		mini_free_envlist (master->envdata);
	if (master->fdstruct->startpath)
		free (master->fdstruct->startpath);
	if (master->envdata)
		free (master->envdata);
	if (master->fdstruct)
		free (master->fdstruct);
	close (master->fdstruct->fd_in);
	close (master->fdstruct->fd_out);
	close (master->fdstruct->fd_err);
}

int	mini_errprint(char *str, char *file, int line, char *func)
{
	perror(str);
	ft_dprintf(2, "Error in %s at line %d in function %s\n", file, line, func);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}
