/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:12:08 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/16 08:43:16 by plavergn         ###   ########.fr       */
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

// char	*rl_get(char *line_read)
// {
// 	if (line_read)
// 		free(line_read);
// 	line_read = readline("coquillette0.1>");
// 	if (!line_read)
// 	{
// 		ft_putendl_fd("exit", 1);
// 		exit(EXIT_SUCCESS);
// 	}
// 	if (line_read && line_read[0])
// 		add_history(line_read);
// 	return (line_read);
// }

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
	while (ft_readline())
		;
	// mini_display_hub(&master, env);
	mini_end_of_program(&master);
	return (0);
}
