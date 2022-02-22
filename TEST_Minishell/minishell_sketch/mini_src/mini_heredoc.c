/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:13:38 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/17 09:51:27 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//vérification de la condition d'arrêt du here_doc
int	mini_check_limiter(char *prompt, char *limiter)
{
	size_t	a;

	a = 0;
	if (!prompt)
		return (0);
	while (prompt[a] != '\n' && limiter[a])
	{
		if (prompt[a] != limiter[a])
			return (1);
		a++;
	}
	if (prompt[a] == '\n' && limiter[a] == '\0')
		return (0);
	return (1);
}

//Here_doc : entrée standard lorsque "<<" est utilisé
//besoin de fork juste avant cette fonction
//Amenée à de possible changement selon les besoin de minishell
//Les variables d'environnement doivent être gérées DANS le here_doc aussi
//Il faut donc une fonction "replace_env_var" ou quelque chose dans le genre
int	mini_heredoc(char *limiter)
{
	char	*prompt;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		mini_print_error(ERR_PIPE, FILE, LINE - 1, FUNC);
	prompt = NULL;
	while (42)
	{
		ft_putstr_fd("Mini here_doc> ", 1);
		prompt = get_next_line(0);
		if (!mini_check_limiter(prompt, limiter))
			break ;
		if (write(pipe_fd[1], prompt, ft_strlen(prompt)) == -1)
			mini_print_error(ERR_WRITE, FILE, LINE -1, FUNC);
		free (prompt);
	}
	free (prompt);
	close (pipe_fd[1]);
	return (pipe_fd[0]);
}
