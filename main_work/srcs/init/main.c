/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:12:08 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/21 13:21:20 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_error_print(char *str, char *file, int line, char *func)
{
	perror(str);
	ft_dprintf(2, "Error in %s at line %d in function %s\n", file, line, func);
	return (1);
}

int	mini_warning_print(char *str, char *file, int line, char *func)
{
	perror(str);
	ft_dprintf(2, "Warning in %s at line %d in function %s\n", file, line, func);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_master	master;

	(void)av;
	if (ac != 1)
		return (mini_error_print(E_AC, DFI, DLI, DFU));
	if (mini_init_master(&master, env))
	{
		mini_end_of_program(&master);
		return (1);
	}
	ft_termios_handler(0);
	while (ft_readline(&master))
		;
	ft_termios_handler(1);
	mini_end_of_program(&master);
	return (0);
}
