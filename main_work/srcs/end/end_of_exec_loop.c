/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_exec_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:30:47 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/02 12:50:08 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_redirection(t_cmd *cmd)
{
	int	i;

	if (ft_strlen(cmd->raw))
	if (ft_isdigit(cmd->raw[0]))
	{
		i = 1;
		//redirection from a particular fd, valid or not
	}
	else
	{
		i = 0;
		//redirection from STDOUT_FILENO / fd_link
	}
	if (cmd->raw[i] == '>' && cmd->raw[i + 1] == '>')
	{
		//open outfile in append mode
	}
	else if (cmd->raw[i] == '>' && cmd->raw[i + 1] != '>')
	{
		if (cmd->raw[i + 1] == '&' && ft_isdigit(cmd->raw[i + 2]))
		{
			//write on a particular fd in trunc mode, valid or not
		}
		else
		{
			//open outfile in trunc mode
		}
	}
	else
	{
		//syntax error ?
	}
}

int	mini_end_of_loop(t_master *master, t_cmd *cmd, int fd_link)
{
	
}