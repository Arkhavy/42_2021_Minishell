/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:35:35 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/19 09:46:01 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**split_echo(char *str, char *dest, t_cmd *cmd)
{
	int	i;
	int	j;

	j = 1;
	i = echo_n(str, ft_int_strchr(str, ' ') + 1);
	if (str[i] == ' ' || str[i] == '"')
	{
		i++;
		cmd->split = malloc(sizeof(char *) * (4));
		cmd->split[1] = ft_strdup("-n");
		j = 2;
	}
	else
	{
		i = cmd->len_cmd;
		cmd->split = malloc(sizeof(char *) * (3));
	}
	while (str[i] && str[i] == ' ')
		i++;
	cmd->split[0] = ft_strdup(dest);
	cmd->len_cmd = count_arg_echo(&str[i]);
	cmd->split[j] = put_without_d_q(&str[i], cmd->split[j], cmd->len_cmd + 1);
	cmd->split[j + 1] = NULL;
	return (cmd->split);
}

/*
char	**split_exit(char *str, char *dest, t_cmd *cmd)
{
	char	*source;
	int		i;

	i = 0;
	source = cmd->raw;
	while (source[i])
	{
		if (source[i] == '|')
			i++;
		i++;
	}
	cmd->split[0] = ft_strdup(cmd);
	cmd->len_cmd = count_arg_echo(&str[i]);
	cmd->split[j] = put_without_d_q(&str[i], cmd->split[j], cmd->len_cmd + 1);
	cmd->split[j + 1] = NULL;
	return (cmd->split);
}
*/

char	**split_unset(char *str, t_cmd *cmd)
{
	cmd->split = ft_split(str, ' ');
	return (cmd->split);
}

char	**split_env(char *dest, t_cmd *cmd)
{
	cmd->split = malloc(sizeof(char *) * (2));
	cmd->split[0] = ft_strdup(dest);
	cmd->split[1] = NULL;
	return (cmd->split);
}

char *export_path_name(char *str, int i, t_cmd *cmd)
{
	int	a;

	a = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && (str[i] != ' ' || str[i] != '='))
	{
		a++;
		i++;
	}
	if (str[i] == '=')
		cmd->split[1] = ft_substr(str, i - a, a);
	else
		cmd->split[1] = NULL;
	return (cmd->split[1]);
}

char *export_path_var(char *str, int i, t_cmd *cmd)
{
	int	a;

	a = 0;
	while (str[i] && str[i] == '=')
		i++;
	while (str[i] && str[i] != ' ')
	{
		a++;
		i++;
	}
	if (str[i] == '=')
		cmd->split[2] = ft_substr(str, i - a, a);
	else
		cmd->split[2] = NULL;
	return (cmd->split[2]);
}

char	**split_export(char *str, char *dest, t_cmd *cmd)
{
	int		i;

	i = ft_strlen(dest);
	cmd->split = malloc(sizeof(char *) * (4));
	cmd->split[0] = ft_strdup(dest);
	cmd->split[1] = export_path_name(str, i, cmd);
	cmd->split[2] = export_path_var(str, i, cmd);
	cmd->split[3] = NULL;
	return (cmd->split);
}

char	**split_pwd(char *dest, t_cmd *cmd)
{
	cmd->split = malloc(sizeof(char *) * (2));
	cmd->split[0] = ft_strdup(dest);
	cmd->split[1] = NULL;
	return (cmd->split);
}

char	**split_cd(char *str, char *dest, t_cmd *cmd)
{
	int		i;
	int		a;

	a = 0;
	i = ft_strlen(dest);
	cmd->split = malloc(sizeof(char *) * (3));
	cmd->split[0] = ft_strdup(dest);
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
	{
		a++;
		i++;
	}
	cmd->split[1] = ft_substr(str, i - a, a);
	cmd->split[2] = NULL;
	return (cmd->split);
}
