/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 08:40:01 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/13 08:39:08 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	case_readline(int i, char *dest, char *s1, t_master *master)
{
	if (i == 4 && ft_strncmp("echo", s1, 4) == 0)
		mini_echo_built_in(&dest);
	else if (i == 3 && ft_strncmp("pwd", s1, 3) == 0)
		mini_pwd_built_in();
	else if (i == 2 && ft_strncmp("cd", s1, 2) == 0)
		mini_cd_built_in(master->envdata, dest);
	else if (i == 3 && ft_strncmp("env", s1, 3) == 0)
		mini_env_built_in(master->envdata);
	else if (i == 4 && ft_strncmp("exit", s1, 4) == 0)
		mini_exit_built_in(master, dest);
	else if (i == 6 && ft_strncmp("export", s1, 6) == 0)
		mini_export_built_in(master->envdata, dest);
	else if (ft_strncmp("unset", s1, 5) == 0)
		mini_unset_built_in(master->envdata, dest);
	else if (ft_strlen(s1) > 0)
		ft_dprintf(1, "%s %s\n", "Morning-shell: Command not found: ", s1);
	else
		rl_clear_history();
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
	if (str[0] == '<' && str[1] == '<')
	{
		cmd = NULL;
		if (i < 0 || i > 2)
			arg = ft_substr(str, 2, ft_strlen(str));
		else
			arg = ft_substr(str, i + 1, ft_strlen(str));
		start_heredoc(arg);
		free (arg);
		return ;
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
	int		i;

	i = 0;
	master->execdata->lst = NULL;
	search_signal();
	str = readline("Morning-shell ➡ ");
	if (!str)
	{
		ft_dprintf(1, "\b\bexit\n");
		ft_termios_handler(1);
		exit(EXIT_FAILURE);
	}
	mini_check_line(str);
	pre_sort(str, master);
	mini_exec_loop(master, dup(STDIN_FILENO));
	add_history(str);
	// free(master->execdata);
	free(str);
	return (1);
}