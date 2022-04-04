/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_envsplit_minishell.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:44:52 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/04 11:47:32 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void	display_envsplit_minishell(t_master *master)
{
	size_t	a;
	char	**envsplit;

	a = 0;
	master->envdata->lst = master->envdata->start;
	envsplit = mini_convert_lst_to_split(master->envdata);
	dprintf(1, "\n\nDISPLAY ENVSPLIT MINISHELL\n\n");
	while (envsplit[a])
	{
		dprintf(1, "%zu:	%s\n", a, envsplit[a]);
		a++;
	}
	ft_free_split(envsplit);
}
