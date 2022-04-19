/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:48:46 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/27 09:39:12 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	size_t	a;
	char	*str;
	int		quote;

	str = ft_strdup("bonjour ceci |est un test| ouaf");
	dprintf(1, "len %zu\n", ft_strlen("bonjour ceci "));
	dprintf(1, "len %zu\n", ft_strlen("est un test"));
	dprintf(1, "len %zu\n", ft_strlen(" ouaf"));
	a = 0;
	quote = 0;
	while (str[a])
	{
		if (str[a] == '|')
			dprintf(1, "ouaf %zu\n", a);
		a++;
	}
	free (str);
	return (0);
}
