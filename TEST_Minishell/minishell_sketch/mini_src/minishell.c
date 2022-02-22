/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 12:52:43 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/21 13:32:22 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_inc/minishell.h"

//Fonction d'affichage d'erreur, à utiliser avec les define dans le .h
int	mini_print_error(char *message, char *file, int line, char *function)
{
	perror(message);
	printf("Error occured in %s at line %d in %s\n", file, line, function);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	if (ac > 1)
		return (mini_print_error(ERR_AC, FILE, LINE - 1, (char *)FUNC));
	return (0);
}
