/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:35:35 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/18 09:44:43 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**split_echo(char *str, char *cmd, int len, char **split)
{
	int	i;
	int	j;

	j = 1;
	i = echo_n(str, ft_int_strchr(str, ' ') + 1);
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
