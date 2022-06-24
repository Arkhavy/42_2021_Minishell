/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:59:48 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/24 07:49:51 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	*check_heredoc(char *str, int *tab_index)
{
	tab_index[0] += 2;
	while (str[tab_index[0]] && str[tab_index[0]] == ' ')
		tab_index[0]++;
	tab_index[1] = tab_index[0];
	while (str[tab_index[0]] && str[tab_index[0]] != ' ')
		tab_index[0]++;
	return (tab_index);
}

int	*check_herefile(char *str, int *tab_index)
{
	tab_index[0]++;
	while (str[tab_index[0]] && str[tab_index[0]] == ' ')
		tab_index[0]++;
	tab_index[1] = tab_index[0];
	while (str[tab_index[0]] && str[tab_index[0]] != ' ')
		tab_index[0]++;
	return (tab_index);
}

int	check_access(char *arg, int heredoc)
{
	if (access(arg, F_OK) == -1)
		heredoc = mini_error(E_ACCESS_F, arg, EACCES) * -1;
	else if (access(arg, R_OK) == -1)
		heredoc = mini_error(E_ACCESS_R, arg, EACCES) * -1;
	else
		heredoc = open(arg, O_RDWR);
	return (heredoc);
}

int	mini_handle_heredoc(char *str, int *tab_index, char **arg, t_master *master)
{
	int	heredoc;

	heredoc = -2;
	*arg = ft_substr(str, tab_index[1], tab_index[0] - tab_index[1]);
	heredoc = start_heredoc(*arg, master);
	free (*arg);
	return (heredoc);
}

int	mini_handle_fd_link(char *str, int *tab_index, char **arg)
{
	int	heredoc;

	heredoc = -2;
	*arg = ft_substr(str, tab_index[1], tab_index[0] - tab_index[1]);
	heredoc = check_access(*arg, heredoc);
	free (*arg);
	return (heredoc);
}

int	ft_heredoc(char *str, t_master *master)
{
	int		heredoc;
	char	*arg;
	int		*tab_index;

	tab_index = init_tab_index();
	heredoc = -2;
	while (str[tab_index[0]])
	{
		if (str[tab_index[0]] == '<' && str[tab_index[0] + 1] == '<')
		{
			tab_index = check_heredoc(str, tab_index);
			heredoc = mini_handle_heredoc(str, tab_index, &arg, master);
		}
		else if (str[tab_index[0]] == '<' && str[tab_index[0] + 1] != '<')
		{
			tab_index = check_herefile(str, tab_index);
			heredoc = mini_handle_fd_link(str, tab_index, &arg);
		}
		else
			tab_index[0]++;
	}
	free(tab_index);
	return (heredoc);
}

void	mini_exec_fd_link(t_master *master, int heredoc)
{
	t_cmd	*cmd;

	cmd = master->execdata->lst->content;
	if (heredoc == -2)
		master->fdstruct->fd_link = dup(STDIN_FILENO);
	else
		master->fdstruct->fd_link = heredoc;
	mini_exec_loop(master);
}

void	check_exit_str_1(char *str, t_master *master)
{
	if (!ft_strncmp(str, "exit",
			ft_get_highest(ft_strlen(str), ft_strlen("exit"))))
		mini_exit_built_in(master, NULL);
}

char	*check_var(t_master *master, char *str)
{
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			quote++;
		if (str[i] == '$' && quote % 2 == 0)
			str = mini_expand_env_var(master->envdata, str, i);
		i++;
	}
	return (str);
}

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			if (str[i] == '\n')
			{
				free(str);
				return (1);
			}
			else
				return (0);
		}
		i++;
	}
	free(str);
	return (1);
}

int	check_return(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\n')
	{
		free(str);
		return (1);
	}
	else
	{
		if (check_space(str) == 1)
			return (1);
		else
			return (0);
	}
	return (0);
}

char	*norm_readline(t_master *master, char *str)
{
	master->execdata->lst = NULL;
	ft_termios_handler(0);
	master->execdata->lst_size = 0;
	search_signal();
	str = readline("Morning-shell ➡ ");
	ft_termios_handler(1);
	check_str_empty(str);
	add_history(str);
	str = check_var(master, str);
	return (str);
}

int	ft_readline(t_master *master)
{
	char	*str;
	int		heredoc;

	str = NULL;
	str = norm_readline(master, str);
	if (check_return(str))
		return (1);
	if (mini_check_line(str))
	{
		free(str);
		return (1);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	heredoc = ft_heredoc(str, master);
	str = pre_sort(un_double_quote(str), master);
	master->execdata->start = master->execdata->lst;
	check_exit_str_1(str, master);
	if (str[0])
		mini_exec_fd_link(master, heredoc);
	mini_free_execdata_list(master->execdata);
	free(str);
	return (1);
}
