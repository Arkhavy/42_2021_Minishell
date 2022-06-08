/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 09:42:47 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/08 13:10:44 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**check_split_builtin(char *dest, char *str, t_cmd *cmd)
{
	if (!ft_strncmp(dest, "echo",
			ft_get_highest(cmd->len_cmd, ft_strlen("echo"))))
		return (split_echo(str, dest, cmd));
	if (!ft_strncmp(dest, "cd",
			ft_get_highest(cmd->len_cmd, ft_strlen("cd"))))
		return (split_cd(str, dest, cmd));
	if (!ft_strncmp(dest, "pwd",
			ft_get_highest(cmd->len_cmd, ft_strlen("pwd"))))
		return (split_pwd(dest, cmd));
	if (!ft_strncmp(dest, "env",
			ft_get_highest(cmd->len_cmd, ft_strlen("env"))))
		return (split_env(dest, cmd));
	if (!ft_strncmp(dest, "export",
			ft_get_highest(cmd->len_cmd, ft_strlen("export"))))
		return (split_export(str, dest, cmd));
	if (!ft_strncmp(dest, "unset",
			ft_get_highest(cmd->len_cmd, ft_strlen("unset"))))
		return (split_unset(str, cmd));
	if (!ft_strncmp(dest, "exit",
			ft_get_highest(cmd->len_cmd, ft_strlen("exit"))))
		return (split_echo(str, dest, cmd));
	return (NULL);
}

char	**check_split_cmd(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i + 1] != '>' || str[i + 1] != '|'))
		i++;
	return (ft_split(ft_substr(str, 0, i), ' '));
}

char	**check_type(char *dest, char *str, t_cmd *cmd)
{
	if (check_builtin(dest, cmd->len_cmd) == 1)
		return (check_split_builtin(dest, str, cmd));
	else
		return (check_split_cmd(str));
}

int	init_cmd(char *str, char *dest, t_master *master)
{
	t_cmd	*cmd;
	char	**tmp;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (mini_error(ENOMEM));
	cmd->raw = ft_strdup(str);
	if (dest[0] != '>' && dest[0] != '&' && !base_fd(dest[0]))
	{
		tmp = ft_split(dest, ' ');
		if (tmp[0])
			cmd->len_cmd = ft_strlen(tmp[0]);
		cmd->token_id = check_token_id(tmp[0], cmd->len_cmd);
		cmd->split = check_type(tmp[0], dest, cmd);
		ft_free_split(tmp);
		ft_lstadd_back(&master->execdata->lst, ft_lstnew(cmd));
		master->execdata->lst_size++;
	}
	else
	{
		cmd->len_cmd = 1;
		cmd->token_id = IDT_REDIR;
		cmd->split = split_redir(dest, cmd);
		ft_lstadd_back(&master->execdata->lst, ft_lstnew(cmd));
		master->execdata->lst_size++;
	}
	return (0);
}

int	check_nb_dq(char *str)
{
	int	i;
	int	d_q;

	i = 0;
	d_q = 0;
	while (str[i])
	{
		if (str[i] == '"')
			d_q++;
		i++;
	}
	return (d_q);
}

char	*un_double_quote(char *str)
{
	int		i;
	int		a;
	char	*dest;

	i = 0;
	a = 0;
	dest = malloc(sizeof(char) * (ft_strlen(str) - check_nb_dq(str) + 1));
	while (str[i])
	{
		if (str[i] != '"')
		{
			dest[a] = str[i];
			a++;
		}
		i++;
	}
	dest[a] = '\0';
	return (dest);
}

int	pre_sort(char *str, t_master *master)
{
	int		tab_index[2];
	char	*dest;

	tab_index[0] = 0;
	tab_index[1] = 0;
	dest = NULL;
	while (str[tab_index[0]])
	{
		// if (base_fd(str[tab_index[0]]))
		// {
		// 	tab_index[1] = check_redir(str, dest, tab_index, master);
		// 	tab_index[0] = tab_index[1];
		// }
		// tab_index[1] = before_redir_check(str, dest, tab_index, master);
		tab_index[1] = redir_check(str, dest, tab_index, master);
		tab_index[1] = pipe_check(str, dest, tab_index, master);
		tab_index[1] = end_check(str, dest, tab_index, master);
		tab_index[0]++;
	}
	return (0);
}
