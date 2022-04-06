/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:43:51 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/29 19:07:33 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_init_master(t_master *master, char **env)
{
	master->envdata = ft_calloc(1, sizeof(t_envdata));
	master->fdstruct = ft_calloc(1, sizeof(t_fd));
	master->parsing = ft_calloc(1, sizeof(t_parsing));
	if (!master->envdata || !master->fdstruct || !master->parsing)
		return (mini_errprint(E_MALLOC, DFI, DLI, DFU));
	master->line = NULL;
	master->nb_tok = 0;
	if (mini_init_envdata(master->envdata, env))
		return (mini_errprint(E_INIT, DFI, DLI, DFU));
	if (mini_init_fdstruct(master->fdstruct))
		return (mini_errprint(E_INIT, DFI, DLI, DFU));
	return (0);
}

int	mini_init_fdstruct(t_fd	*fdstruct)
{
	fdstruct->fd_in = dup(STDIN_FILENO);
	fdstruct->fd_out = dup(STDOUT_FILENO);
	fdstruct->fd_err = dup(STDERR_FILENO);
	if (fdstruct->fd_in < 0 || fdstruct->fd_out < 0 || fdstruct->fd_err < 0)
		return (mini_errprint(E_DUP, DFI, DLI, DFU));
	fdstruct->startpath = getcwd(NULL, 0);
	if (!fdstruct->startpath)
		return (mini_errprint(E_MALLOC, DFI, DLI, DFU));
	return (0);
}

// void	mini_init_state(t_state *state)
// {
// 	state->normal = 1;
// 	state->d_quote = 0;
// 	state->s_quote = 0;
// 	state->dollar = 0;
// 	state->option = 0;
// }

// int	mini_init_parsing(t_parsing *parsing, char *prompt)
// {
// 	size_t		a;
// 	t_prompt	*prompt;
// 	t_state		*state;
// 	char		*save;

// 	a = 0;
// 	parsing->lst = NULL;
// 	parsing->lst_size = 0;
// 	save = NULL;
// 	state = malloc(sizeof(t_state));
// 	if (!state)
// 		return (mini_errprint(E_MALLOC, DFI, DLI, DFU));
// 	while (prompt[a])
// 	{
// 		mini_init_state(state);
// 		if (!mini_check_state(state, prompt, &a, &save))
// 			mini_handle_state(state, prompt, &a, &save);
// 		a++;
// 	}
// 	parsing->start = parsing->lst;
// 	free(state);
// }
