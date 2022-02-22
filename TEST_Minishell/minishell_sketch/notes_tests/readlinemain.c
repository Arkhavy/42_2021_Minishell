/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlinemain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 08:20:55 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/14 08:50:13 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//gcc -Wall -Werror -Wextra -I mini_inc -I libft/lib_includes -lreadline *.c
int	main(void)
{
	char	*prompt;
	char	*str;

	while (1)
	{
		prompt = "This is a prompt>";
		str = readline(prompt);
		dprintf(1, "prompt:%s\n", str);
		if (!strncmp(str, "exit", 6))
		{
			free (str);
			return (0);
		}
		// rl_clear_history()
		free (str);
	}
	return (0);
}