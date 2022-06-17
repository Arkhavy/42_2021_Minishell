/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:35:39 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/18 11:06:25 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_str_empty(char *str)
{
	if (!str)
	{
		ft_dprintf(1, "\b\bexit\n");
		ft_termios_handler(1);
		exit(EXIT_FAILURE);
	}
}

void	check_exit_str(t_master *master)
{
	t_cmd	*cmd;

	master->execdata->lst = master->execdata->start;
	cmd = master->execdata->lst->content;
	printf("%sw\n", cmd->split[0]);
	if (!ft_strncmp(cmd->split[0], ft_strdup("exit"), 4))
		mini_exit_built_in(master, NULL);
}
