/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 07:31:27 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/23 11:38:45 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_termios_handler(int end)
{
	struct termios			termios_p;
	static struct termios	termios_before;
	int						fd_term;

	fd_term = ttyslot();
	if (end == 1)
	{
		tcsetattr(fd_term, TCSANOW, &termios_before);
		return ;
	}
	tcgetattr(fd_term, &termios_before);
	termios_p = termios_before;
	termios_p.c_cc[VQUIT] = 0;
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(fd_term, TCSANOW, &termios_p);
}

//(  | ICANON)

void	handler(int byte)
{
	(void)byte;
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_dprintf(0, "\n");
	rl_redisplay();
}

void	search_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
}

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
