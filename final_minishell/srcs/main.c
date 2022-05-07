/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 12:57:27 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/07 13:13:25 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_end_of_program(t_master *master)
{
	if (master->envdata)
	{
		master->envdata->lst = master->envdata->start;
		if (master->envdata->lst)
			mini_free_envdata_list(master->envdata);
		if (master->envdata->paths)
			ft_free_split(master->envdata->paths);
		free (master->envdata);
	}
	if (master->execdata)
	{
		master->execdata->lst = master->execdata->start;
		if (master->execdata->lst)
			mini_free_execdata_list(master->execdata);
		free (master->execdata);
	}
	if (master->fdstruct)
	{
		free (master->fdstruct);
	}
}

int	mini_error(char *str, char *arg, int err_id, int warning)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	if (arg)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	g_mini_errno = err_id;
	return (warning);
}

int	main(int ac, char **av, char **env)
{
	t_master	*master;

	if (ac != 1)
		return (mini_error(E_AC, NULL, N_AC, 1));
	if (mini_init_master(&master, env))
	{
		mini_end_of_program(&master);
		return (1);
	}
}
