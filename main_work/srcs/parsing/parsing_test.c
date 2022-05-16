/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 09:42:47 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/16 09:17:10 by ljohnson         ###   ########lyon.fr   */
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
	return (0);
}

int	check_token_id(char *split, int len_cmd)
{
	int	token_id;
	int	i;

	i = 0;
	if (ft_strncmp(split, ">", ft_get_highest(len_cmd, ft_strlen(">"))) == 0)
		token_id = IDT_REDIR;
	else if (check_builtin(split, len_cmd) == 1)
		token_id = IDT_BTIN;
	else
		token_id = IDT_CMD;
	return (token_id);
}

int	init_cmd(char *str, char *dest, t_master *master)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (mini_error(ENOMEM));
	cmd->raw = ft_strdup(str);
	cmd->split = ft_split(dest, ' '); //fix
	cmd->len_cmd = ft_strlen(cmd->split[0]);
	cmd->token_id = check_token_id(cmd->split[0], cmd->len_cmd);
	ft_lstadd_back(&master->execdata->lst, ft_lstnew(cmd));
	master->execdata->lst_size++;
	return (0);
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
			dest = ft_substr(str, a, i - a - 1);
			printf("%s\n", dest);
			if (init_cmd(str, dest, master))
			{
				free (dest);
				return (1);
			}
			free(dest);
			a = i + 2;
			dest = NULL;
		}
		else if (str[i] == '>')
		{
			dest = ft_substr(str, a, i - a - 1);
			printf("%s\n", dest);
			if (init_cmd(str, dest, master))
			{
				free (dest);
				return (1);
			}
			free(dest);
			a = i;
			dest = NULL;
		}
		else if (str[i + 1] == '\0')
		{
			dest = ft_substr(str, a, i - a + 1);
			printf("%s\n", dest);
			if (init_cmd(str, dest, master))
			{
				free (dest);
				return (1);
			}
			free(dest);
			dest = NULL;
		}
		i++;
	}
	return (0);
}
