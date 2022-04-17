/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:07:26 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/17 11:47:49 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//checker les erreurs de syntaxe symbole into \0
//check le & tout seul aussi
//attention parenthèse
//need more test "'"

// hors de double ou simple quotes
// if [{()}]\;&^%#@*,.:
// if || &&
	// retour erreur E_SUPPORT
// if | ou < ou > ou << ou >>
	// et les char autour sont autre chose qu'alnum / quotes
		//retour erreur E_SYNTAX

// if $
	// expand unless in simple quotes

int	mini_check_line(char *line)
{
	int		a;
	int		len;
	char	quote;
	char	symbol;

	if (!line)
		return (2);
	len = ft_strlen(line);
	a = 0;
	quote = '\0';
	symbol = '\0';
	while (line[a])
	{
		if (line[a] == '"' || line[a] == '\'')
		{
			quote = line[a];
			a++;
			while (line[a] && line[a] != quote)
				a++;
			if (!line[a])
				return (mini_error_print(E_QUOTE, DFI, DLI, DFU));
		}
		if (line[a] && (ft_ischarset(line[a], "[{()}]\\;&^%#@*,.:")
				|| (line[a] == '|' && line[a + 1] == '|')
				|| (line[a] == '&' && line[a + 1] == '&')))
			return (mini_error_print(E_SUPPORT, DFI, DLI, DFU));
		if (line[a] && ft_ischarset(line[a], "|<>"))
		{
			symbol = line[a];
			a++;
			while (line[a] && line[a] == ' ')
				a++;
			if (!line[a] || (ft_ischarset(line[a], "|<>") && line[a] != symbol))
				return (mini_error_print(E_SYNTAX, DFI, DLI, DFU));
			if (line[a] && ft_ischarset(line[a], "[{()}]\\;&^%#@*,.:"))
				return (mini_error_print(E_SUPPORT, DFI, DLI, DFU));
		}
		a++;
	}
	return (0);
}
