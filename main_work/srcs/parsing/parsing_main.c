/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:07:26 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/16 10:26:27 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_open_state_loop(char *line, char opener, int a, int len)
{
	char	closer;

	if (opener == '(')
		closer = ')';
	else if (opener == '[')
		closer = ']';
	else if (opener == '{')
		closer = '}';
	else if (opener == '"' || opener == '\'')
		closer = opener;
	else
		closer = '\0';
	a++;
	while (line[a])
	{
		if (((line[a] == '"' || line[a] == '\'') && line[a] != closer)
			|| line[a] == '(' || line[a] == '[' || line[a] == '{')
			a = mini_open_state_loop(line, line[a], a, len);
		if (a < 0 || a >= len)
			return (-1);
		if (line[a] == closer)
			return (a);
		a++;
	}
	return (-1);
}

int	mini_check_line(char *line)
{
	int	a;
	int	len;

	a = 0;
	if (!line)
		return (0);
	len = ft_strlen(line);
	while (line[a])
	{
		if (line[a] == '"' || line[a] == '\''
			|| line[a] == '(' || line[a] == '[' || line[a] == '{')
			a = mini_open_state_loop(line, line[a], a, len);
		if (a < 0 || a > len || (line[a] == '&' && line[a + 1] == '|')
			|| (line[a] == '|' && line[a + 1] == '&') || line[a] == ')')
			return (mini_error_print(E_SYNTAX, DFI, DLI, DFU));
		if (!line[a])
			return (0);
		if (line[a] == ';' || line[a] == '\\'
			|| (line[a] == '&' && line[a + 1] == '&')
			|| (line[a] == '|' && line[a + 1] == '|'))
			return (mini_error_print(E_SUPPORT, DFI, DLI, DFU));
		a++;
	}
	return (0);
}

//checker les erreurs de syntaxe symbole into \0