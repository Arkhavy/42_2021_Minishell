// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parsing_checker_line.c                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/03/20 15:25:35 by ljohnson          #+#    #+#             */
// /*   Updated: 2022/03/25 14:40:51 by ljohnson         ###   ########lyon.fr   */
// /*                                                                            */
// /* ************************************************************************** */

// #include <minishell.h>

// void	skip_space(char **line)
// {
// 	while (**line == ' ')
// 		(*line)++;
// }

// int	check_succesive_ope(char **line)
// {
// 	char	*tmp;
// 	char	*tmp2;

// 	*tmp = (*line) + 1;
// 	skip_space(&tmp);
// 	if (*tmp)
// 	{
// 		tmp2 = tmp + 1;
// 		skip_space(&tmp2);
// 	}
// 	else
// 		tmp2 = NULL;
// 	if (*tmp && *tmp == '|')
// 			; //ERR
// 	else if (*line != '|' && (*tmp && ft_strchr("|<>", *tmp))) //Manque différents check d'erreur
// 			; //ERR
// 	else
// 		return (0);
// 	return (1);
// }

// int	loop_line(char *line, char *quote, char *last)
// {
// 	*quote = 0;
// 	*last = 0;
// 	while (*line)
// 	{
// 		if (*line != ' ')
// 			*last = *line;
// 		else if ((*line == '"' || *line == '\'') && !*quote)
// 			*quote = *line;
// 		else if (*quote == *line)
// 			*quote = 0;
// 		else if (ft_strchr("|<>", *line) && !*quote)
// 		{
// 			if (check_succesive_ope(&line))
// 				return (1);
// 		}
// 		line++;
// 	}
// 	return (0);
// }

// int	check_line(char *line)
// {
// 	char	quote;
// 	char	last;

// 	skip_space(&line);
// 	if (*line == '|')
// 	{
// 		//ERR
// 		return (1);
// 	}
// 	if (loop_line(line, &quote, &last))
// 		return (1);
// 	if (quote)
// 	{
// 		//ERR
// 		return (1);
// 	}
// 	if (last)
// 	{
// 		//ERR
// 		return (1);
// 	}
// 	return (0);
// }
