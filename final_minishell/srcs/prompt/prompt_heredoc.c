/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 08:36:49 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/08 10:05:40 by ljohnson         ###   ########lyon.fr   */
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

int	mini_check_limiter(char *prompt, char *limiter)
{
	size_t	a;

	a = 0;
	if (!prompt || !limiter)
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

// void	add_prompt(char *str)
// {
// }

int	mini_heredoc(char *limiter)
{
	char	*prompt;
	int		pipe_fd[2];
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		if (pipe(pipe_fd) == -1)
			printf("error\n");
		prompt = NULL;
		while (1)
		{
			search_signal_heredoc();
			prompt = readline(">");
			if (!mini_check_limiter(prompt, limiter))
				break ;
			if (parsing_var(prompt) == 0)
			{
				printf("non\n");
			}
			if (write(pipe_fd[1], prompt, ft_strlen(prompt)) == -1)
				printf("error\n");
			if (write(pipe_fd[1], "\n", 1) == -1)
				printf("error\n");
			free (prompt);
		}
		if (write(pipe_fd[1], "\b", 1) == -1)
			printf("error\n");
		free (prompt);
		close (pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
	return (pipe_fd[0]);
}

int	ft_strlen_char(char *str, char c, int start)
{
	while (str[start] && str[start] != c)
		start++;
	return (start);
}

void	do_after_limiter(char *str)
{
	printf("bien le bonjour :\n%s\n", str);

	exit(EXIT_SUCCESS);
}

int	start_heredoc(char *str)
{
	char	*limiter;
	int		limiter_int;
	int		fd;
	int		j;

	j = 1;
	str = check_char(str);
	signal(SIGINT, SIG_IGN);
	limiter_int = ft_int_strchr(str, ' ');
	if (limiter_int < 0)
		limiter_int = ft_strlen(str);
	limiter = ft_substr(str, 0, limiter_int);
	fd = mini_heredoc(limiter);
	if (ft_strlen(str) > (size_t)limiter_int)
	{
		return (1);
	}
	return (0);
}
