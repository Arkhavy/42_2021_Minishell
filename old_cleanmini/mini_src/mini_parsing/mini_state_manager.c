/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_state_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 11:10:27 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/26 11:44:34 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_handle_state(t_state *state, char *prompt, int *a, char *save)
{
	
}

int	mini_check_state(t_state *state, char *prompt, int *a, char *save)
{
	size_t	b;

	b = *a;
	while (prompt[*a])
	{
		if (prompt[*a] == '\"')
			mini_set_state(state, state->d_quote);
		else if (prompt[*a] == '\'')
			mini_set_state(state, state->s_quote);
		else if (prompt[*a] == '$')
			mini_set_state(state, state->dollar);
		else if (prompt[*a] == '-')
			mini_set_state(state, state->option);
		if (!state->normal)
		{
			free (save);
			save = ft_substr(prompt, b, *a);
			return (0);
		}
		*a++;
	}
	return (1);
}

void	mini_set_state(t_state *state, int *first_state)
{
	*first_state = 1;
	if (state->normal == 1)
		state->normal = 0;
	else
		state->normal = 1;
}
