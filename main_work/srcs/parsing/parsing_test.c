/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 09:42:47 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/06 10:54:39 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int parsing_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i - 1] != '\'')
		{
			while (str[i] && (str[i] != ' ' || str[i] != '\''))
				i++;
			if (str[i] != '\'')
				return (1);
		}
		i++;
	}
	return (0);
}

int parsing_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i - 1] != '\'')
		{
			while (str[i] && (str[i] != ' ' || str[i] != '\''))
				i++;
			if (str[i] != '\'')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_builtin(char *split, int len_cmd)
{

	if (!ft_strncmp(split, "echo",
			ft_get_highest(len_cmd, ft_strlen("echo"))))
		return (1);
	if (!ft_strncmp(split, "pwd",
			ft_get_highest(len_cmd, ft_strlen("pwd"))))
		return (1);
	if (!ft_strncmp(split, "env",
			ft_get_highest(len_cmd, ft_strlen("env"))))
		return (1);
	if (!ft_strncmp(split, "exit",
			ft_get_highest(len_cmd, ft_strlen("exit"))))
		return (1);
	if (!ft_strncmp(split, "export",
			ft_get_highest(len_cmd, ft_strlen("export"))))
		return (1);
	if (!ft_strncmp(split, "unset",
			ft_get_highest(len_cmd, ft_strlen("unset"))))
		return (1);
	if (!ft_strncmp(split, "cd",
			ft_get_highest(len_cmd, ft_strlen("cd"))))
		return (1);
/*
	if (ft_strncmp(split, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(split, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(split, "env", 4) == 0)
		return (1);
	if (ft_strncmp(split, "exit", 4) == 0)
		return (1);
	if (ft_strncmp(split, "export", 4) == 0)
		return (1);
	if (ft_strncmp(split, "unset", 4) == 0)
		return (1);
	if (ft_strncmp(split, "cd", 4) == 0)
		return (1);
*/
	return (0);
}

int	check_token_id(char **split, int len_cmd)
{
	int	token_id;
	int	i;

	i = 0;
	while (split[i])
	{
		if (ft_strncmp(split[0], ">", 1) == 0)
			token_id = IDT_REDIR;
		else if (check_builtin(split[0], len_cmd) == 1)
			token_id = IDT_BTIN;
		else
			token_id = IDT_CMD;
		i++;
	}
	return (token_id);
}

void	init_cmd(char *str, char *dest, t_master *master)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->raw = str;
	cmd->split = ft_split(dest, ' ');
	cmd->len_cmd = ft_strlen(cmd->split[0]);
	cmd->token_id = check_token_id(cmd->split, cmd->len_cmd);
	ft_lstadd_back(&master->execdata->lst, ft_lstnew(cmd));
}

int	pre_sort(char *str, t_master *master)
{
	int		i;
	int		a;
	char	*dest;

	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			dest = ft_substr(str, a, i);
			printf("%sl\n", dest);
			init_cmd(str, dest, master);
			free(dest);
			a = i + 2;
			dest = NULL;
		}
		else if (str[i] == '>')
		{
			dest = ft_substr(str, a, i + 1);
			init_cmd(str, dest, master);
			free(dest);

			dest = NULL;
		}
		else if (str[i + 1] == '\0')
		{
			dest = ft_substr(str, a, i + 1);
			printf("%sl\n", dest);
			init_cmd(str, dest, master);
			free(dest);
			dest = NULL;
		}
		i++;
	}
	return (0);
}
