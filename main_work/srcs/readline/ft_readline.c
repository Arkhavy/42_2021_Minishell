/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 08:40:01 by plavergn          #+#    #+#             */
/*   Updated: 2022/04/20 09:27:13 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	handler(int byte)
{
	if (byte == 2)
	{
		ft_dprintf(1, "Morning-shell ➡   \b\b\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (byte == 3)
	{
		rl_replace_line("   ", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	search_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

static void	case_readline(int i, char *dest, char *s1, t_master *master)
{
	if (i == 4 && strncmp("echo", s1, 4) == 0)
		mini_echo_built_in(dest, 0);
	else if (i == 3 && strncmp("pwd", s1, 3) == 0)
		mini_pwd_built_in();
	else if (i == 2 && strncmp("cd", s1, 2) == 0)
		mini_cd_built_in(master->envdata, dest);
	else if (i == 3 && strncmp("env", s1, 3) == 0)
		mini_env_built_in(master->envdata);
	else if (i == 4 && strncmp("exit", s1, 4) == 0)
		mini_exit_built_in(master, dest);
	else if (i == 6 && strncmp("export", s1, 6) == 0)
		mini_export_built_in(master->envdata, dest);
	else if (strncmp("unset", s1, 5) == 0)
		mini_unset_built_in(master->envdata, dest);
	else if (ft_strlen(s1) > 0)
		ft_dprintf(1, "%s %s\n", W_CMD, s1);
}

void	readline_exec(char *str, t_master *master)
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
	case_readline(ft_strlen(cmd), arg, cmd, master);
	free (cmd);
	free (arg);
	return ;
}

int	ft_readline(t_master *master)
{
	char	*str;

	search_signal();
	str = readline("Morning-shell ➡ ");
	if (!str)
	{
		ft_dprintf(1, "\b\bexit\n");
		exit(EXIT_FAILURE);
	}
	add_history(str);
	readline_exec(str, master);
	free(str);
	return (1);
}
