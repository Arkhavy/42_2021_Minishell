/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 09:42:47 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/17 08:53:20 by plavergn         ###   ########.fr       */
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

int	count_d_q_word(char *str)
{
	int	i;
	int	d_q;

	i = 0;
	d_q = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			d_q++;
		}
		else if (str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
			d_q++;
		}
		else
			i++;
	}
	return (d_q);
}

char	**double_quote(char *str)
{
	int		i;
	int		j;
	int		a;
	char	**split;

	i = 0;
	j = 0;
	a = 0;
	split = malloc(sizeof(char *) * (count_d_q_word(str) + 1));
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			split[j] = ft_substr(str, i, ft_int_strchr(&str[i], '"'));
			j++;
			while (str[i] && str[i] != '"')
				i++;
		}
		else if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			split[j] = ft_substr(str, i, ft_int_strchr(&str[i], ' '));
			j++;
		}
		else if (str[i + 1] == '\0')
		{
			split[j] = ft_substr(str, i, ft_int_strchr(&str[i], '\0'));
			j++;
		}
		else
			i++;
	}
	split[j] = NULL;
	return (split);
}

int	init_cmd(char *str, char *dest, t_master *master, int d_q)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (mini_error(ENOMEM));
	cmd->raw = ft_strdup(str);
	if (d_q == 1)
		cmd->split = double_quote(dest);
	else
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
	int		d_q;
	char	*dest;

	i = 0;
	a = 0;
	d_q = 0;
	while (str[i])
	{
		if (str[i] == '"')
			d_q = 1;
		if (str[i] == '|')
		{
			dest = ft_substr(str, a, i - a - 1);
			// printf("%s\n", dest);
			if (init_cmd(str, dest, master, d_q))
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
			// printf("%s\n", dest);
			if (init_cmd(str, dest, master, d_q))
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
			// printf("%s\n", dest);
			if (init_cmd(str, dest, master, d_q))
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
