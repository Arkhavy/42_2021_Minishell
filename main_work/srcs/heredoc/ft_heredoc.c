/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 08:36:49 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/02 12:55:24 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	mini_check_limiter(char *prompt, char *limiter)
{
	size_t	a;

	a = 0;
	if (!prompt)
		return (0);
	while (prompt[a] != '\0' && limiter[a])
	{
		if (prompt[a] != limiter[a])
			return (1);
		a++;
	}
	if (prompt[a] == '\0' && limiter[a] == '\0')
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
	// int		pipe_fd[2];
	int		fd;

//	if (pipe(pipe_fd) == -1)
//		mini_print_error(ERR_PIPE, DFI, DLI, DFU);
	prompt = NULL;
	while (1)
	{
		// ft_putstr_fd("Mini here_doc> ", 1);
		prompt = readline(">");
		// printf("%s\n", prompt);
		// ft_putstr_fd(prompt, fd);
		if (!mini_check_limiter(prompt, limiter))
			break ;
//		if (write(pipe_fd[1], prompt, ft_strlen(prompt)) == -1)
//			mini_print_error(ERR_DEF, DFI, DLI, DFU);
		// free (prompt);
	}
	// free (prompt);
//	close (pipe_fd[1]);
	fd = dup(STDIN_FILENO);
	read(fd, &prompt, 9000);
	printf("%s", prompt);
	return (0);
}

int	ft_strlen_char(char *str, char c, int start)
{
	while (str[start] && str[start] != c)
		start++;
	return (start);
}

void	start_heredoc(char *str)
{
	char	*limiter;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Fork Failed");
		return ;
	}
	else if (pid == 0)
	{
		limiter = ft_substr(str, 4, ft_strlen_char(str, ' ', 3));
		printf("%s\n", limiter);
		mini_heredoc(limiter);
		printf("I'm the child \n");
	}
	else
	{
		wait(NULL);
		printf("Child Complete \n");
	}
}
