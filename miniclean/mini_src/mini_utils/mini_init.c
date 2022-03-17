/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:43:51 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/17 13:55:58 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_test.h>

int	mini_init_master(t_master *master, char **env)
{
	master->envdata = NULL;
	master->fdstruct = NULL;
	master->token = NULL;
	master->line = NULL;
	master->nb_tok = 0;
	if (mini_init_envdata(master->envdata, env))
		return (mini_errprint(E_INIT, DFI, DLI, DFU));
	if (mini_init_fdstruct(master->fdstruct))
		return (mini_errprint(E_INIT, DFI, DLI, DFU));
	return (0);
}

int	mini_init_envdata(t_envdata *envdata, char **env)
{
	size_t	a;
	t_env	*env_var;

	a = 0;
	envdata->lst = NULL;
	envdata->lst_size = 0;
	envdata->envmain = env;
	while (env[a])
	{
		env_var = malloc(sizeof(t_env));
		if (!env_var)
			return (mini_errprint(E_MALLOC, DFI, DLI, DFU));
		env_var->name = ft_substr(env[a], 0, ft_int_strchr(env[a], '='));
		env_var->value = ft_substr(env[a],
				ft_int_strchr(env[a], '=') + 1, ft_strlen(env[a]));
		ft_lstadd_back(&envdata->lst, ft_lstnew(env_var));
		envdata->lst_size++;
		a++;
	}
	envdata->start = envdata->lst;
	envdata->paths = mini_get_paths(env);
	if (!envdata->paths)
		return (mini_errprint(E_MALLOC, DFI, DLI, DFU));
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

static size_t	nb_pipe(char *line)
{
	size_t	nb_pipe;
	char	quote;

	nb_pipe = 0;
	quote = 0;
	while (*line)
	{
		if ((*line == '"' || *line == '\'') && !quote)
			quote = *line;
		else if (quote == *line)
			quote = 0;
		if (*line == '|' && !quote)
			nb_pipe++;
		line++;
	}
	return (nb_pipe);
}

int	mini_init_token(t_master *master)
{
	size_t	i;

	master->nb_tok = nb_pipe(master->line);
	master->token = ft_calloc(master->nb_tok, sizeof(t_token));
	if (!master->token)
		return (mini_errprint(E_MALLOC, DFI, DLI, DFU));
	i = -1;
	while (++i < master->nb_tok)
	{
		master->token[i].fd_in = 0;
		master->token[i].fd_out = 1;
		master->token[i].cmd = NULL;
		master->token[i].path = NULL;
	}
	return (0);
}
