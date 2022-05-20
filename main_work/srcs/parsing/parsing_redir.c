/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:42:11 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/20 09:48:24 by plavergn         ###   ########.fr       */
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

char	**find_case(char *str, t_cmd *cmd)
{
	int	i;
	int	redir;
	int	fd;
	int	fd_char;
	int	ampersand;

	i = 0;
	fd_char = 1;
	fd = 0;
	ampersand = 0;
	redir = 0;
	while (str[i])
	{
		if (fd_char == 1 && base_fd(str[i]) && (base_fd(str[i - 1]) || str[i - 1] == ' '))
			fd++;
		else if (fd_char == 1 && base_fd(str[i]) && (base_fd(str[i - 1]) == 0 || str[i - 1] != ' '))
			fd_char = 0;
		if (str[i] == '>')
		{
			while (str[i] && str[i] == '>')
			{
				redir++;
				i++;
			}
		}
		if (str[i] == '&' && redir == 1)
			ampersand++;
		i++;
	}
	if (fd == 0 && redir == 1 && ampersand == 0)
		return (redir_alone(str, cmd));
	if (fd == 0 && redir == 2 && ampersand == 0)
		return (redir_double(str, cmd));
	if (fd == 0 && redir == 1 && ampersand == 1)
		return (redir_ampersand(str, cmd));
	if (fd > 0 && redir == 1 && ampersand == 0)
		return (redir_fd(str, cmd));
	if (fd > 0 && redir == 2 && ampersand == 0)
		return (redir_double_fd(str, cmd));
	if (fd > 0 && redir == 1 && ampersand == 1)
		return (redir_fd_ampersand(str, cmd));
	return (NULL);
}

char	**split_redir(char *dest, t_cmd *cmd)
{
	return (find_case(dest, cmd));
}


// Split[0] = nombre si il existe sinon > ou >> ou >&
// Split[1] = > ou >> ou >& si Split[0] = nombre sinon c'est fd_out qui peut être un int si >& sinon c'est un nom de fichier
// Split[2] = NULL si Split[0] is not digit sinon fd_out



// 3 parties
// p1 = fd_in (facultatif)
// p2 = > ou >> ou >&
// p3 = fd_out : int if part 2 == >& else fichier

// if (p1)
// 	Split[0] = p1;
// 	Split[1] = p2;
// 	Split[2] = p3;
// 	Split[3] = NULL;
// else
// 	Split[0] = p2;
// 	Split[1] = p3;
// 	Split[2] = NULL;

// if (p2 == >>)
// 	p3 = open (file, O_WRONLY | O_CREAT | O_APPEND, 0766)
// else if (p2 == >&)
// 	p3 = dup(ft_atoi(p3))
// else
// 	p3 = open (file, O_WRONLY | O_CREAT | O_TRUNC, 0766)
