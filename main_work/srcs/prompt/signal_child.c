/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:38:32 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/23 16:39:18 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handler_here(int byte)
{
	(void)byte;
	printf("\n");
	exit(EXIT_SUCCESS);
}

void	search_signal_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_here);
}

void	handler_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	handler_cat(int byte)
{
	if (byte == SIGINT)
		printf("\n");
	else if (byte == SIGQUIT)
	{
		printf("Quit: 3\n");
	}
}
