/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:35:35 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/18 15:24:23 by plavergn         ###   ########.fr       */
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

// char	**split_pwd(char *str, char *dest, t_cmd *cmd)
// {
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	split[0] = cmd;
// }

// char	**split_env(char *str, char *dest, t_cmd *cmd)
// {
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	split[0] = cmd;
// }

// char	**split_export(char *str, char *dest, t_cmd *cmd)
// {
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	split[0] = cmd;
// }

// char	**split_unset(char *str, char *dest, t_cmd *cmd)
// {
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	split[0] = cmd;
// }

// char	**split_cd(char *str, char *dest, t_cmd *cmd)
// {
// 	char	**split;
// 	int		i;

// 	i = 0;
// 	split[0] = cmd;
// }
