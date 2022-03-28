/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 10:31:38 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/28 13:21:14 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_free_parsinglist(t_parsing *parsing)
{
	t_token	*token;
	void	*tmp;

	parsing->lst = parsing->start;
	token = NULL;
	while (parsing->lst)
	{
		token = parsing->lst->content;
		free (token->raw_cmd);
		token->len = 0;
		free (parsing->lst->content);
		tmp = parsing->lst;
		parsing->lst = parsing->lst->next;
		free (tmp);
	}
}

int	mini_check_errors(char *prompt)
{
	size_t	a;
	int		is_in_quotes;
	char	quote;

	a = 0;
	is_in_quotes = 0;
	quote = '\0';
	while (prompt[a])
	{
		a = mini_skip_space(prompt, a);
		if ((prompt[a] == '"' || prompt[a] == '\'') && is_in_quotes == 0)
		{
			is_in_quotes = 1;
			quote = prompt[a];
			a++;
		}
		if (prompt[a] && prompt[a] == quote && is_in_quotes == 1)
			is_in_quotes = 0;
		if ((prompt[a] == '\\' || prompt[a] == ';') && is_in_quotes == 0)
			return (mini_errprint(E_CONTENT, DFI, DLI, DFU));
		a++;
	}
	if (is_in_quotes == 1)
		return (mini_errprint(E_QUOTE, DFI, DLI, DFU));
	return (0);
}

int	mini_init_parsing(t_master *master, char *prompt)
{
	t_parsing	parsing;
	t_list		*tmp;
	size_t		tmp_size;

	parsing.lst = NULL;
	tmp = NULL;
	tmp_size = 0;
	parsing.lst_size = 0;
	if (!prompt)
		return (mini_errprint(E_EMPTY, DFI, DLI, DFU));
	if (mini_check_errors(prompt))
		return (1);
	if (mini_pipe_cut(tmp, prompt))
		return (mini_errprint(E_PARSING, DFI, DLI, DFU));
	tmp_size = ft_lstsize(tmp);
	// while (tmp)
	// {
	// 	mini_next_cut_idk_what_it_will_be_yet(tmp, parsing);
	// 	tmp = tmp->next;
	// }
	parsing.start = parsing.lst;
	master->parsing = &parsing;
	return (0);
}
