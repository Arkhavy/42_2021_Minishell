/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:59:48 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/25 12:12:15 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	do_export(char *str, t_master *master)
{
	t_cmd	*cmd;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(str, ' ');
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (mini_error(E_MALLOC, NULL, ENOMEM));
	cmd->raw = ft_strdup(str);
	if (tmp[0])
		cmd->len_cmd = ft_strlen(tmp[0]);
	cmd->token_id = IDT_BTIN;
	cmd->split = split_export(str);
	ft_free_split(tmp);
	ft_lstadd_back(&master->execdata->lst, ft_lstnew(cmd));
	master->execdata->lst_size++;
	printf("kfuygekyrfr [%s]\n", cmd->split[0]);
	return (1);
}

int	check_export(char *str, t_master *master)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(str, ' ');
	if (!ft_strncmp(tmp[0], "export",
			ft_get_highest(ft_strlen(tmp[0]), ft_strlen("export"))))
		return (do_export(str, master));
	return (0);
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
	if (!check_export(str, master))
		str = pre_sort(un_dblequote(str), master);
	master->execdata->start = master->execdata->lst;
	check_exit_str_1(str, master);
	if (str[0])
		mini_exec_fd_link(master, heredoc);
	mini_free_execdata_list(master->execdata);
	free(str);
	return (1);
}
