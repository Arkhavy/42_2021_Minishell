/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pre_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:08:45 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/22 14:16:51 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	pipe_check(char *str, char *dest, int *tab_index, t_master *master)
{
	int	i;
	int	a;

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

int	check_base_fd(char *str, int i)
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
	return (i);
}

int	skip_redir(char *str, int i, int *tab_index)
{
	if (i != tab_index[0])
	{
		while (str[i] && str[i] != '>')
			i++;
		while (str[i] && str[i] == '>')
			i++;
		while (str[i] && str[i] != '|' && str[i] != '>')
			i++;
	}
	else
	{
		while (str[i] && str[i] == '>')
			i++;
		while (str[i] && str[i] != '|' && str[i] != '>')
			i++;
	}
	return (i);
}

int	redir_check(char *str, char *dest, int *tab_index, t_master *master)
{
	int		i;
	int		a;
	char	*tmp;

	i = tab_index[0];
	a = tab_index[1];
	if (str[i] == '>')
	{
		i = check_base_fd(str, i);
		a = i;
		if (a > tab_index[1])
		{
			tmp = ft_substr(str, tab_index[1], a - tab_index[1]);
			init_cmd(str, tmp, master);
			free(tmp);
		}
		i = skip_redir(str, i, tab_index);
		dest = ft_substr(str, a, i - a);
		init_cmd(str, dest, master);
		free(dest);
		if (!str[i])
			return (-1);
		a = i;
	}
	return (a);
}

int	end_check(char *str, char *dest, int *tab_index, t_master *master)
{
	int	i;
	int	a;

	i = tab_index[0];
	a = tab_index[1];
	if (str[i + 1] == '\0' && tab_index[1] > -1)
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
