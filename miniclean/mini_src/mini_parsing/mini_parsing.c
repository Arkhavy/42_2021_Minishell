/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:33:03 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/20 15:47:01 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Get an argument from the line
char	*get_args(char *line)
{
	char	*start;
	char	*quote;

	start = line;
	quote = 0;
	while (*line && (ft_strchr("|<>", *line) || quote || start == line))
	{
		if ((*line == '"' || *line == '\'') && !quote)
			*quote = *line;
		else if (*quote == *line)
			*quote = 0;
		line++;
	}
	start = ft_substr(start, 0, line - start);
	if (!start)
		; //ERR
	return (start);
}

//Get one command from the line
int	get_command(char **line, size_t i)
{
	char	*tmp;
	tmp = get_args(line);
	if (!tmp)
	{
		;//ERR
		return (1);
	}
	return (0);
}

//Fill each token with all informations
int	fill_token(t_master *master)
{
	size_t	i;

	i = 0;
	while (*(master->line) && i < master->nb_tok)
	{
		skip_space(&master->line);
		if (get_command(&master->line, i))
			return (1);
		if (*(master->line) == '<' /*AND INFILE ERR*/)
			return (1);
		else if (*(master->line) == '>' /*AND OUTFILE ERR*/)
			return (1);
		else if (*(master->line) == '|' || !*(master->line))
			i++;
	}
	return (0);
}

int	parsing(t_master *master)
{
	if (check_line(master->line) || mini_init_token(master))
		return (1);
	return (0);
}
