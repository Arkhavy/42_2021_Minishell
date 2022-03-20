/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:58:11 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/20 15:41:38 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_end_of_program(t_master *master)
{
	master->envdata->lst = master->envdata->start;
	if (master->envdata->paths)
		ft_free_split (master->envdata->paths);
	if (master->envdata)
		mini_free_envlist (master->envdata);
	if (master->fdstruct->startpath)
		free (master->fdstruct->startpath);
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

//Loop servant à récupérer les données envoyé dans minishell via readline
// int	loop_readline(t_master *master)
// {
// 	while (1)
// 	{
// 		if (g_error)
// 			master->line = readline(PROMPT_ERR);
// 		else
// 			master->line = readline(PROMPT);
// 		parsing(master);
// 	}
// 	ft_free_split(master->envdata->paths);
// 	mini_free_envlist(master->envdata);
// 	free (master->fdstruct->startpath);
// 	return (0);
// }

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}
