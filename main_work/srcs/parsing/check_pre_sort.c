/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pre_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:08:45 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/13 10:42:36 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int pipe_check(char *str, char *dest, int *tab_index, t_master *master)
{
	int i;
	int a;

	i = tab_index[0];
	a = tab_index[1];
	if (str[i] == '|')
	{
		dest = ft_substr(str, a, i - a - 1);
		if (init_cmd(str, dest, master))
		{
			free(dest);
			return (1);
		}
		free(dest);
		a = i + 2;
	}
	return (a);
}
/*
char	*check_cmd_before(char *str, int *tab_index)
{
	int		index[2];
	int		count;
	char	*tmp1;
	char	**tmp;
	char	**dest;

	index[0] = 0;
	index[1] = 0;
	count = 0;
	tmp1 = ft_substr(str, tab_index[1], tab_index[0]);
	tmp = split(tmp1, ' ');
	while (tmp[index[0]])
	{
		while (tmp[index[0]][index[1]])
		{
			if (!base_fd(tmp[index[0]][index[1]]))
			{
				count++;
				break ;
			}
			index[1]++;
		}
		index[0]++;
	}
	if (count == index[0])
		return (NULL);
	else if (count + 1 == index[0])
		return (tmp[index[0]]);
	else
		return (NULL);
}
*/
int redir_check(char *str, char *dest, int *tab_index, t_master *master)
{
	int i;
	int a;

	i = tab_index[0];
	a = tab_index[1];
	if (str[i] == '>')
	{
		if ((i > 0 && base_fd(str[i - 1])) || (str[i + 1] && str[i + 1] == '>'))
		{
			if (i > 0 && base_fd(str[i - 1]))
			{
				i--;
				while (i > 0 && str[i] && base_fd(str[i]))
					i--;
				if (i > 0)
					i++;
			}
		}
		// else if (i > 0 && str[i - 1] == '&')
		// 	i--;
		a = i;
		if (a > tab_index[1])
			init_cmd(str, ft_substr(str, tab_index[1], a - tab_index[1]), master);
		if (i != tab_index[0])
		{
			while (str[i] && str[i] != '>')
				i++;
			while (str[i] && str[i] == '>')
				i++;
			while (str[i] && (str[i] != '|' || str[i] != '>'))
				i++;
		}
		else if (a > tab_index[1])
			while (str[i] && (str[i] != '|' || str[i] != '>'))
				i++;
		dest = ft_substr(str, a, i - a);
		if (init_cmd(str, dest, master))
		{
			free(dest);
			return (1);
		}
		free(dest);
		a = i;
	}
	return (a);
}

int check_redir(char *str, char *dest, int *tab_index, t_master *master)
{
	int i;

	i = tab_index[0];
	while (str[tab_index[0]] && base_fd(str[tab_index[0]]))
		tab_index[0]++;
	while (str[tab_index[0]] && str[tab_index[0]] == ' ')
		tab_index[0]++;
	if (str[tab_index[0]] && str[tab_index[0]] == '>' && (str[tab_index[1] - 1] == ' ' || str[tab_index[1] - 1] == '|'))
	{
		dest = ft_substr(str, tab_index[1], i - tab_index[1] - 1);
		if (init_cmd(str, dest, master))
		{
			free(dest);
			return (1);
		}
		free(dest);
		return (i);
	}
	return (tab_index[1]);
}

int end_check(char *str, char *dest, int *tab_index, t_master *master)
{
	int i;
	int a;

	i = tab_index[0];
	a = tab_index[1];
	if (str[i + 1] == '\0')
	{
		dest = ft_substr(str, a, i - a + 1);
		if (init_cmd(str, dest, master))
		{
			free(dest);
			return (1);
		}
		free(dest);
	}
	return (a);
}