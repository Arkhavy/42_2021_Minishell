/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:43:50 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/23 16:39:39 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	*ouioui(int *tab_index, char *str)
{
	tab_index[0]++;
	while (str[tab_index[0]] && (str[tab_index[0]] == ' '
			|| str[tab_index[0]] == '>'))
		tab_index[0]++;
	tab_index[1] = tab_index[0];
	while (str[tab_index[1]])
		tab_index[1]++;
	return (tab_index);
}

int	*test_norm(int *tab_index, char *str)
{
	tab_index[0]++;
	while (str[tab_index[0]] && str[tab_index[0]] == ' ')
		tab_index[0]++;
	tab_index[1] = tab_index[0];
	while (str[tab_index[1]])
		tab_index[1]++;
	return (tab_index);
}

char	*init_split(char *str, int *tab_index)
{
	char	*tmp;

	while (str[tab_index[0]] && str[tab_index[0]] != '>')
		tab_index[0]++;
	tmp = malloc(sizeof(char) * (tab_index[0] + 1));
	if (!tmp)
	{
		mini_error(E_MALLOC, NULL, ENOMEM);
		return (NULL);
	}
	tmp[tab_index[0]] = '\0';
	return (tmp);
}
