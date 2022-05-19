/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pre_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:08:45 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/19 13:13:16 by plavergn         ###   ########.fr       */
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
			free (dest);
			return (1);
		}
		free(dest);
		a = i + 2;
	}
	return (a);
}

int	redir_check(char *str, char *dest, int *tab_index, t_master *master)
{
	int	i;
	int	a;

	i = tab_index[0];
	a = tab_index[1];
	if (str[i] == '>')
	{
		while (str[i] && str[i] != '|')
			i++;
		dest = ft_substr(str, a, i - a);
		printf("%s\n", dest);
		if (init_cmd(str, dest, master))
		{
			free (dest);
			return (1);
		}
		free(dest);
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
	if (str[i + 1] == '\0')
	{
		dest = ft_substr(str, a, i - a + 1);
		if (init_cmd(str, dest, master))
		{
			free (dest);
			return (1);
		}
		free(dest);
	}
	return (a);
}
