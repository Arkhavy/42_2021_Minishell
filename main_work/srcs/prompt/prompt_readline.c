/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 08:40:01 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/23 14:55:28 by plavergn         ###   ########.fr       */
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
			arg = ft_substr(str, tab_index[1], tab_index[0] - tab_index[1]);
			heredoc = start_heredoc(arg, master);
			free (arg);
		}
		else if (str[tab_index[0]] == '<' && str[tab_index[0] + 1] != '<')
		{
			tab_index = check_herefile(str, tab_index);
			arg = ft_substr(str, tab_index[1], tab_index[0] - tab_index[1]);
			if (access(arg, F_OK) == -1)
			{
				free (arg);
				heredoc = mini_error(E_ACCESS_F, arg, EACCES, DFI, DLI, DFU) * -1;
			}
			else if (access(arg, R_OK) == -1)
			{
				free (arg);
				heredoc = mini_error(E_ACCESS_R, arg, EACCES, DFI, DLI, DFU) * -1;
			}
			else
			{
				heredoc = open(arg, O_RDWR);
				free (arg);
			}
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
	if (master->fdstruct->fd_link == -1)
		return ;
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
	return (0);
}

int	ft_readline(t_master *master)
{
	char	*str;
	int		heredoc;
	int		i;

	i = 0;
	master->execdata->lst = NULL;
	ft_termios_handler(0);
	master->execdata->lst_size = 0;
	search_signal();
	str = readline("Morning-shell ➡ ");
	ft_termios_handler(1);
	check_str_empty(str);
	add_history(str);
	str = check_var(master, str);
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
