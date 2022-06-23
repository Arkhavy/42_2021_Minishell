/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:42:11 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/23 13:31:38 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	base_fd(char str)
{
	int		i;
	char	*base;

	i = 0;
	base = ft_strdup("0123456789");
	while (base[i])
	{
		if (str == base[i])
		{
			free(base);
			return (1);
		}
		i++;
	}
	free(base);
	return (0);
}

char	**tri_case(int *tab_case, char *str, t_cmd *cmd)
{
	int	redir;
	int	fd;

	fd = tab_case[0];
	redir = tab_case[1];
	free(tab_case);
	if (fd == 0 && redir == 1)
		return (redir_alone(str, cmd));
	if (fd == 0 && redir == 2)
		return (redir_double(str, cmd));
	if (fd > 0 && redir == 1)
		return (redir_fd(str, cmd));
	if (fd > 0 && redir == 2)
		return (redir_double_fd(str, cmd));
	return (NULL);
}

char	**find_case(char *str, t_cmd *cmd)
{
	int	i;
	int	*tab_case;
	int	fd_char;

	i = 0;
	fd_char = 1;
	tab_case = init_tab_index();
	while (str[i])
	{
		if (fd_char == 1 && base_fd(str[i])
			&& ((i > 0 && base_fd(str[i - 1])) || (i > 0 && str[i - 1] == ' ')))
			tab_case[0]++;
		else if (fd_char == 1 && base_fd(str[i])
			&& (i > 0 && base_fd(str[i - 1]) == 0)
			&& (i > 0 && str[i - 1] != ' '))
			fd_char = 0;
		else if (i == 0 && base_fd(str[i]))
			tab_case[0]++;
		if (str[i] == '>')
			tab_case[1]++;
		i++;
	}
	return (tri_case(tab_case, str, cmd));
}

char	**split_redir(char *dest, t_cmd *cmd)
{
	return (find_case(dest, cmd));
}
