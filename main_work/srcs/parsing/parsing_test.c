/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 09:42:47 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/17 14:23:06 by plavergn         ###   ########.fr       */
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

int	count_echo(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			a++;
		}
		else if (str[i] == ' ' && a == 0)
		{
			while (str[i] && str[i] == ' ')
				i++;
			a++;
		}
		else
			i++;
	}
	return (a);
}

// int	count_pwd(char *str)
// {}

// int	count_env(char *str)
// {}

// int	count_exit(char *str)
// {}

// int	count_export(char *str)
// {}

// int	count_unset(char *str)
// {}

// int	count_cd(char *str)
// {}

int	count_arg_echo(char *str)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '"')
			len++;
		i++;
	}
	return (len);
}

char	*put_without_d_q(char *str, char *split, int len)
{
	int	i;
	int	a;

	a = 0;
	i = 0;
	split = malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		if (str[i] != '"')
		{
			split[a] = str[i];
			a++;
		}
		i++;
	}
	split[a] = '\0';
	return (split);
}

char	**split_echo(char *str, char *cmd, int len, char **split)
{
	int	i;
	int	j;

	j = 1;
	i = ft_int_strchr(str, ' ') + 1;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		i++;
		while (str[i] && str[i] != ' ' && str[i] == 'n')
			i++;
	}
	else if (str[i] == '"' && str[i + 1] == '-')
	{
		i += 2;
		while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] == 'n')
			i++;
	}
	if (str[i] == ' ' || str[i] == '"')
	{
		i++;
		split = malloc(sizeof(char *) * (4));
		split[1] = ft_strdup("-n");
		j = 2;
	}
	else
	{
		i = len;
		split = malloc(sizeof(char *) * (3));
	}
	while (str[i] && str[i] == ' ')
		i++;
	split[0] = ft_strdup(cmd);
	len = count_arg_echo(&str[i]);
	split[j] = put_without_d_q(&str[i], split[j], len + 1);
	split[j + 1] = NULL;
	return (split);
}

// char	**split_pwd(char *str, char *cmd, int len)
// {
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	split[0] = cmd;
// }

// char	**split_env(char *str, char *cmd, int len)
// {
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	split[0] = cmd;
// }

// char	**split_exit(char *str, char *cmd, int len)
// {
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	split[0] = cmd;
// }

// char	**split_export(char *str, char *cmd, int len)
// {
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	split[0] = cmd;
// }

// char	**split_unset(char *str, char *cmd, int len)
// {
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	split[0] = cmd;
// }

// char	**split_cd(char *str, char *cmd, int len)
// {
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	split[0] = cmd;
// }


char	**check_split(char *cmd, char *str, int len, char **split)
{
	if (!ft_strncmp(cmd, "echo",
			ft_get_highest(len, ft_strlen("echo"))))
		return (split_echo(str, cmd, len, split));
	// if (!ft_strncmp(cmd, "pwd",
	// 		ft_get_highest(len, ft_strlen("pwd"))))
	// 	return (split_pwd(str, cmd, len));
	// if (!ft_strncmp(cmd, "env",
	// 		ft_get_highest(len, ft_strlen("env"))))
	// 	return (split_env(str, cmd, len));
	// if (!ft_strncmp(cmd, "exit",
	// 		ft_get_highest(len, ft_strlen("exit"))))
	// 	return (split_exit(str, cmd, len));
	// if (!ft_strncmp(cmd, "export",
	// 		ft_get_highest(len, ft_strlen("export"))))
	// 	return (split_export(str, cmd, len));
	// if (!ft_strncmp(cmd, "unset",
	// 		ft_get_highest(len, ft_strlen("unset"))))
	// 	return (split_unset(str, cmd, len));
	// if (!ft_strncmp(cmd, "cd",
	// 		ft_get_highest(len, ft_strlen("cd"))))
	// 	return (split_cd(str, cmd, len));
	return (NULL);
}

int	init_cmd(char *str, char *dest, t_master *master, int d_q)
{
	t_cmd	*cmd;
	char	**tmp;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (mini_error(ENOMEM));
	cmd->raw = ft_strdup(str);
	(void) d_q;
	// if (d_q == 1 || d_q == 0)
	// 	cmd->split = double_quote(dest);
	tmp = ft_split(dest, ' ');
	cmd->len_cmd = ft_strlen(tmp[0]);
	cmd->token_id = check_token_id(tmp[0], cmd->len_cmd);
	cmd->split = check_split(tmp[0], dest, cmd->len_cmd, cmd->split);
	ft_free_split(tmp);
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
