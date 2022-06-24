/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:35:35 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/24 08:11:41 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**split_malloc(t_cmd *cmd, int nb)
{
	cmd->split = malloc(sizeof(char *) * (nb));
	if (!cmd->split)
	{
		mini_error(E_MALLOC, NULL, ENOMEM);
		return (NULL);
	}
	return (cmd->split);
}

static void	init_split_echo(t_cmd *cmd, char *dest, char *str, int j)
{
	cmd->split[0] = ft_strdup(dest);
	cmd->len_cmd = count_arg_echo(str);
	cmd->split[j] = put_without_d_q(str, cmd->split[j], cmd->len_cmd + 1);
	cmd->split[j + 1] = NULL;
}

int	mini_increment_i(char *str, int i)
{
	if (str[i])
		if (str[i + 1])
			i++;
	return (i);
}

char	**split_echo(char *str, char *dest, t_cmd *cmd)
{
	int	i;
	int	j;

	j = 1;
	i = echo_n(str, ft_int_strchr(str, ' ') + 1);
	if (str[i] == ' ' || str[i] == '"' || !str[i])
	{
		i = mini_increment_i(str, i);
		cmd->split = split_malloc(cmd, 4);
		if (!cmd->split)
			return (NULL);
		cmd->split[1] = ft_strdup("-n");
		j = 2;
	}
	else
	{
		i = cmd->len_cmd;
		cmd->split = split_malloc(cmd, 3);
		if (!cmd->split)
			return (NULL);
	}
	while (str[i] && str[i] == ' ')
		i++;
	init_split_echo(cmd, dest, &str[i], j);
	return (cmd->split);
}

char	**split_exit(char *str, char *dest, t_cmd *cmd)
{
	char	*source;
	int		i;
	int		a;

	a = 0;
	i = ft_strlen(dest);
	source = cmd->raw;
	while (source[i])
	{
		if (source[i] == '|')
		{
			exit(EXIT_FAILURE);
		}
		i++;
	}
	cmd->split = ft_split(str, ' ');
	return (cmd->split);
}

char	**split_unset(char *str, t_cmd *cmd)
{
	cmd->split = ft_split(str, ' ');
	return (cmd->split);
}

char	**split_env(char *dest, t_cmd *cmd, char *str)
{
	(void)dest;
	(void)cmd;
	return (ft_split(str, ' '));
}
