/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 09:42:47 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/05 15:10:26 by plavergn         ###   ########.fr       */
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

void	init_cmd(char *str, char *dest, t_master *master, char c)
{
	int		i;
	// int		a;
	// char	*dest;
	t_cmd	*cmd;

/*
struct s_cmd
{
	int		token_id;
	char	*raw;
	char	**split;
	int		len_cmd;
};
*/
	// master->execdata->lst = master->execdata->start;
	// master->execdata->lst = ft_lstlast(master->execdata->lst);
	cmd = malloc(sizeof(t_cmd));
	cmd->raw = str;
	cmd->token_id = c;
	cmd->len_cmd = ft_strlen(dest);
	i = 0;
	cmd->split = ft_split(dest, ' ');
	while (cmd->split[i])
	{
		printf("%s\n", cmd->split[i]);
		i++;
	}
	// printf("\n\nabcd\nresult:\n");
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
		if (str[i] == '|' || str[i] == '>')
		{
			dest = ft_substr(str, a, i);
			init_cmd(str, dest, master, str[i]);
			a = i + 1;
		}
		else if (str[i +1] == '\0')
		{
			dest = ft_substr(str, a, i + 1);
			init_cmd(str, dest, master, '\0');
		}
		i++;
	}
	return (0);
}
