/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 10:31:38 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/27 10:05:14 by ljohnson         ###   ########lyon.fr   */
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

int	mini_init_parsing(t_master *master, char *prompt)
{
	t_parsing	parsing;

	parsing.lst = NULL;
	parsing.lst_size = 0;
	if (!prompt)
		return (mini_errprint(E_PROMPT, DFI, DLI, DFU));
	if (mini_pipe_cut(&parsing, prompt))
		return (mini_errprint(E_PARSING, DFI, DLI, DFU));
	parsing.start = parsing.lst;
	master->parsing = &parsing;
	return (0);
}
