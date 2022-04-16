/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 08:40:01 by plavergn          #+#    #+#             */
/*   Updated: 2022/04/16 12:55:03 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	handler(int byte)
{
	if (byte == 2)
	{
		printf("\n");
	}
	if (byte == 3)
	{
		printf("\b\b");
	}
}

int	search_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	return (1);
}

static void	case_readline(int i, char *dest, char *s1)
{
	if (i == 5 && strncmp("echo", s1, 4) == 0)
		mini_echo_built_in(dest, 0);
	else if (i == 4 && strncmp("pwd", s1, 3) == 0)
		mini_pwd_built_in();
	else if (i == 3 && strncmp("^D", s1, 2) == 0)
		exit(EXIT_FAILURE);
	else if (i == 3 && strncmp("^C", s1, 2) == 0)
	{
		printf("q");
		printf("\n");
		return ;
	}
	// else if (i == 2 && strncmp("cd", s1, 2) == 0)
	// 	mini_cd_built_in(envdata, dest);
	// else if (i == 3 && strncmp("env", s1, 3) == 0)
	// 	mini_env_built_in(envdata);
	// else if (i == 4 && strncmp("exit", s1, 4) == 0)
	// 	mini_exit_built_in(master, dest);
	// else if (i == 6 && strncmp("export", s1, 6) == 0)
	// 	mini_export_built_in(envdata, dest);
	// else if (strncmp("unset", s1, 5) == 0)
	// 	mini_unset_built_in(envdata, dest);
	else
		printf("%s %s\n", W_CMD, s1);
}

void	readline_exec(char *str)
{
	char	*cmd;
	char	*arg;
	int		i;

	i = ft_int_strchr(str, ' ');
	if (i < 0)
	{
		cmd = ft_strdup(str);
		arg = NULL;
	}
	else
	{
		cmd = ft_substr(str, 0, i);
		arg = ft_substr(str, i + 1, ft_strlen(str) - i);
	}
	case_readline(i, arg, cmd);
	free (cmd);
	free (arg);
	return ;
}

// void	readline_exec(char *str)
// {
// 	char	*s1;
// 	char	*dest;
// 	int		i;

// 	i = 0;
// 	while (str[i] && str[i] != ' ')
// 		i++;
// 	s1 = malloc(sizeof(char) * (i + 1));
// 	if (!s1)
// 		return ;
// 	i = -1;
// 	while (str[i++] && str[i] != ' ')
// 		s1[i] = str[i];
// 	s1[i] = '\0';
// 	ft_choose(str, s1, dest);
// 	if (str[i] != '\0')
// 	{
// 		dest = ft_substr(str, i + 1, ft_strlen(str));
// 		case_readline(i + 1, dest, s1);
// 	}
// 	else
// 	{
// 		dest = ft_strdup("");
// 		case_readline(i, dest, s1);
// 	}
// 	free(dest);
// 	free(s1);
// 	return ;
// }

int	ft_readline(void)
{
	char	*str;

	str = readline("Morning-shell ➡");
	if (!str)
	{
		printf("\b\bexit\n");
		exit(EXIT_FAILURE);
	}
	if (search_signal() == 2)
		return (1);
	if (mini_check_line(str) == 1)
		return (0);
	add_history(str);
	readline_exec(str);
	free(str);
	return (1);
}
