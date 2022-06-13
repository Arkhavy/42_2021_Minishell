/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 08:40:01 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/13 10:30:56 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_heredoc(char *str)
{
	int		heredoc;
	char	*arg;
	int		i;

	i = ft_int_strchr(str, ' ');
	if (str[0] == '<' && str[1] == '<')
	{
		if (i < 0 || i > 2)
			arg = ft_substr(str, 2, ft_strlen(str));
		else
			arg = ft_substr(str, i + 1, ft_strlen(str));
		heredoc = start_heredoc(arg);
		free (arg);
	}
	else
		return (-1);
	return (heredoc);
}

void	mini_exec_fd_link(t_master *master, int heredoc)
{
	t_cmd	*cmd;

	cmd = master->execdata->lst->content;
	// master->fdstruct->fd_link = heredoc;
	// if (heredoc > -1)
	// 	mini_exec_loop(master);
	// else
	// 	mini_exec_loop(master);
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

void	print_exec(t_master *master)
{
	t_cmd	*cmd;
	int		i;

	master->execdata->lst = master->execdata->start;
	cmd = master->execdata->lst->content;
	while (master->execdata->lst)
	{
		cmd = master->execdata->lst->content;
		i = 0;
		while (cmd->split[i])
		{
			printf("split numero %d : |%s|\n", i, cmd->split[i]);
			i++;
		}
		master->execdata->lst = master->execdata->lst->next;
	}
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
	str = mini_expand_env_var(master->envdata, str, ft_int_strchr(str, '$'));
	if (str[0] == '\n')
		return (1);
	if (mini_check_line(str))
		return (1);
	pre_sort(un_double_quote(str), master);
	master->execdata->start = master->execdata->lst;
	check_exit_str_1(str, master);
	heredoc = ft_heredoc(str);
	if (str[0] != 0)
		mini_exec_fd_link(master, heredoc);
	print_exec(master);
	mini_free_execdata_list(master->execdata);
	free(str);
	return (1);
}
