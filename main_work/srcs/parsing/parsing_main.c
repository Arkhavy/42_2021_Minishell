/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:07:26 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/03 08:56:48 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//checker les erreurs de syntaxe symbole into \0
//need more test

// hors de double ou simple quotes
// if [{()}]\;&^%#@*,.:
// if || &&
	// retour erreur E_SUPPORT
// if | ou < ou > ou << ou >>
	// et les char autour sont autre chose qu'alnum / quotes
		//retour erreur E_SYNTAX

// if $
	// expand unless in simple quotes

int	mini_loop_quote(char *line, char quote, int a)
{
	while (line[a] && line[a] != quote)
		a++;
	if (!line[a])
		return (mini_error_print(E_QUOTE, DFI, DLI, DFU) * -1);
	return (a);
}

int	mini_check_supported_char(char *line, int a)
{
	if (line[a] && ft_ischarset(line[a], "[{()}]\\;&^%#@*,:"))
		return (mini_error_print(E_SUPPORT, DFI, DLI, DFU));
	else if (line[a] && (line[a] == '|' && line[a + 1] == '|'))
		return (mini_error_print(E_SUPPORT, DFI, DLI, DFU));
	else if (line[a] && (line[a] == '&' && line[a + 1] == '&'))
		return (mini_error_print(E_SUPPORT, DFI, DLI, DFU));
	return (0);
}

int	mini_check_syntax(char *line, char symbol, int a)
{
	while (line[a] && line[a] == ' ')
		a++;
	if (!line[a] || (ft_ischarset(line[a], "|<>") && line[a] != symbol))
		return (mini_error_print(E_SYNTAX, DFI, DLI, DFU) * -1);
	if (line[a] && ft_ischarset(line[a], "[{()}]\\;&^%#@*,.:"))
		return (mini_error_print(E_SUPPORT, DFI, DLI, DFU) * -1);
	return (a);
}

int	mini_check_line(char *line)
{
	int		a;

	if (!line)
		return (2);
	a = 0;
	while (line[a])
	{
		if (line[a] == '"' || line[a] == '\'')
			a = mini_loop_quote(line, line[a], a + 1);
		if (a < 0)
			return (1);
		if (mini_check_supported_char(line, a))
			return (1);
		if (line[a] && ft_ischarset(line[a], "|<>"))
			a = mini_check_syntax(line, line[a], a + 1);
		if (a < 0)
			return (1);
		if (line[a])
			a++;
	}
	return (0);
}

//Ordre de parsing
	//Check syntaxe
	//Séparation des commandes, built-ins et redirection
	//Suppression des quotes
		//Here_doc si existant
			//Expand des variables d'environnement
	//Expand des variables d'environnement
	//Lancement de l'exécution