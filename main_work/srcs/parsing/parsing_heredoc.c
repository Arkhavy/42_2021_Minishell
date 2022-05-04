/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 09:00:42 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/04 09:13:23 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*check_char(char *line)
{
	int		a;
	int		i;
	char	*str;

	if (!line)
		return (NULL);
	a = 0;
	i = 0;
	while (line[a])
	{
		if (line[a] == '"' || line[a] == '\'')
			a++;
		else if (line[a])
		{
			a++;
			i++;
		}
	}
	str = malloc(sizeof(char) * (i + 1));
	a = 0;
	i = 0;
	while (line[a])
	{
		if (line[a] == '"' || line[a] == '\'')
			a++;
		else if (line[a])
		{
			str[i] = line[a];
			a++;
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}
