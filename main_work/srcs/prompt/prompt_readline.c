/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 08:40:01 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/22 13:56:20 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_heredoc(char *str, t_master *master)
{
	int		heredoc;
	char	*arg;
	int		*tab_index;

	tab_index = init_tab_index();
	heredoc = -1;
	while (str[tab_index[0]])
	{
		if (str[tab_index[0]] == '<' && str[tab_index[0] + 1] == '<')
		{
			tab_index[0] += 2;
			while (str[tab_index[0]] && str[tab_index[0]] == ' ')
				tab_index[0]++;
			tab_index[1] = tab_index[0];
			while (str[tab_index[0]] && str[tab_index[0]] != ' ')
				tab_index[0]++;
			arg = ft_substr(str, tab_index[1], tab_index[0] - tab_index[1]);
			heredoc = start_heredoc(arg, master);
			free (arg);
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
	if (heredoc == -1)
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

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
			str = mini_expand_env_var(master->envdata, str, i);
		i++;
	}
	return (str);
}

int	ft_readline(t_master *master)
{
	char	*str;
	int		heredoc;
	int		i;

	i = 0;
	master->execdata->lst = NULL;
	master->execdata->lst_size = 0;
	search_signal();
	str = readline("Morning-shell ➡ ");
	check_str_empty(str);
	add_history(str);
	str = check_var(master, str);
	if (str[0] == '\n')
		return (1);
	if (mini_check_line(str))
		return (1);
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
