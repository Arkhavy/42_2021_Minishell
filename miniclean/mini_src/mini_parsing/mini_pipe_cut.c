/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe_cut.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:32:41 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/27 13:07:58 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_init_token(t_list *lst, char *prompt, size_t a, size_t b)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (mini_errprint(E_MALLOC, DFI, DLI, DFU) * -1);
	token->raw_cmd = ft_substr(prompt, b, a - b);
	token->len = ft_strlen(token->raw_cmd);
	ft_lstaddback(&lst, ft_lstnew(token));
	return (a + 1);
}

size_t	mini_skip_space(char *prompt)
{
	size_t	a;

	a = 0;
	while (prompt[a] == ' ')
		a++;
	return (a);
}

size_t	mini_check_quotes(char *prompt, char *quote, int *is_in_quotes)
{
	size_t	a;

	a = 0;
	if ((prompt[a] == '"' || prompt[a] == '\'') && *is_in_quotes == 0)
	{
		*is_in_quotes = 1;
		*quote = prompt[a];
		a++;
	}
	return (a);
}

int	mini_pipe_cut(t_list *lst, char *prompt)
{
	size_t	a;
	size_t	b;
	int		is_in_quotes;
	char	quote;

	is_in_quotes = 0;
	a = 0;
	b = 0;
	quote = '\0';
	while (prompt[a])
	{
		a = mini_skip_space(prompt);
		a += mini_check_quotes(prompt, &quote, &is_in_quotes);
		if (prompt[a] == quote && is_in_quotes == 1)
			is_in_quotes = 0;
		if (prompt[a] == '|' && is_in_quotes == 0)
			b = mini_init_token(lst, prompt, a, b);
		if (b < 0)
			return (1);
		a++;
	}
	return (0);
}
