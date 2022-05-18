/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pre_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:08:45 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/18 10:10:44 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	pipe_check(char *str, char *dest, int i, int a, t_master *master)
{
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
		dest = NULL;
	}
	return (a);
}

int	redir_check(char *str, char *dest, int i, int a, t_master *master)
{
	if (str[i] == '>')
	{
		dest = ft_substr(str, a, i - a - 1);
		if (init_cmd(str, dest, master))
		{
			free (dest);
			return (1);
		}
		free(dest);
		a = i;
		dest = NULL;
	}
	return (a);
}

int	end_check(char *str, char *dest, int i, int a, t_master *master)
{
	if (str[i + 1] == '\0')
	{
		dest = ft_substr(str, a, i - a + 1);
		if (init_cmd(str, dest, master))
		{
			free (dest);
			return (1);
		}
		free(dest);
		dest = NULL;
	}
	return (a);
}
