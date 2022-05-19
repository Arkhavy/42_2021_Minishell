/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 09:42:47 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/19 08:38:41 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
/*
int	count_pwd(char *str)
{}

int	count_env(char *str)
{}

int	count_exit(char *str)
{}

int	count_export(char *str)
{}

int	count_unset(char *str)
{}

int	count_cd(char *str)
{}
*/

/*
	if (!ft_strncmp(cmd, "env",
			ft_get_highest(len, ft_strlen("env"))))
		return (split_env(str, cmd, len));
	if (!ft_strncmp(cmd, "export",
			ft_get_highest(len, ft_strlen("export"))))
		return (split_export(str, cmd, len));
	if (!ft_strncmp(cmd, "unset",
			ft_get_highest(len, ft_strlen("unset"))))
		return (split_unset(str, cmd, len));
	if (!ft_strncmp(dest, "exit",
			ft_get_highest(cmd->len_cmd, ft_strlen("exit"))))
		return (split_echo(str, dest, cmd));
*/
char	**check_split(char *dest, char *str, t_cmd *cmd)
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
	return (NULL);
}

int	init_cmd(char *str, char *dest, t_master *master)
{
	t_cmd	*cmd;
	char	**tmp;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (mini_error(ENOMEM));
	cmd->raw = ft_strdup(str);
	tmp = ft_split(dest, ' ');
	cmd->len_cmd = ft_strlen(tmp[0]);
	cmd->token_id = check_token_id(tmp[0], cmd->len_cmd);
	cmd->split = check_split(tmp[0], dest, cmd);
	ft_free_split(tmp);
	ft_lstadd_back(&master->execdata->lst, ft_lstnew(cmd));
	master->execdata->lst_size++;
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
		tab_index[1] = pipe_check(str, dest, tab_index, master);
		tab_index[1] = redir_check(str, dest, tab_index, master);
		tab_index[1] = end_check(str, dest, tab_index, master);
		tab_index[0]++;
	}
	return (0);
}
