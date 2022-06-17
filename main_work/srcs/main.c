/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 12:57:27 by ljohnson          #+#    #+#             */
/*   Updated: 2022/06/17 09:55:23 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
//ouaf
void	mini_free_execdata_list(t_execdata *execdata)
{
	t_cmd	*cmd;
	void	*tmp;

	execdata->lst = execdata->start;
	cmd = NULL;
	tmp = NULL;
	while (execdata->lst)
	{
		cmd = execdata->lst->content;
		free (cmd->raw);
		cmd->raw = NULL;
		ft_free_split(cmd->split);
		cmd->split = NULL;
		cmd->token_id = 0;
		cmd->len_cmd = 0;
		free (execdata->lst->content);
		execdata->lst->content = NULL;
		tmp = execdata->lst;
		execdata->lst = execdata->lst->next;
		free (tmp);
		tmp = NULL;
	}
}

void	mini_free_envdata_list(t_envdata *envdata)
{
	t_env	*env_var;
	void	*tmp;

	envdata->lst = envdata->start;
	env_var = NULL;
	tmp = NULL;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		free (env_var->name);
		env_var->name = NULL;
		free (env_var->value);
		env_var->value = NULL;
		env_var->name_len = 0;
		env_var->index = 0;
		free (envdata->lst->content);
		envdata->lst->content = NULL;
		tmp = envdata->lst;
		envdata->lst = envdata->lst->next;
		free (tmp);
		tmp = NULL;
	}
}

void	mini_end_of_program(t_master *master)
{
	if (master->envdata)
	{
		master->envdata->lst = master->envdata->start;
		if (master->envdata->lst)
			mini_free_envdata_list(master->envdata);
		if (master->envdata->paths)
			ft_free_split(master->envdata->paths);
		free (master->envdata);
	}
	if (master->execdata)
	{
		master->execdata->lst = master->execdata->start;
		if (master->execdata->lst)
			mini_free_execdata_list(master->execdata);
		free (master->execdata);
	}
	if (master->fdstruct)
	{
		mini_reset_fdstruct(master->fdstruct);
		mini_close_fdstruct(master->fdstruct);
		free (master->fdstruct);
	}
}

int	mini_error(int err_id)
{
	g_mini_errno = err_id;
	ft_dprintf(STDERR_FILENO, "\033[31m\033[1m%s\033[0m\n", strerror(err_id));
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_master	master;

	(void)av;
	if (ac != 1)
		return (mini_error(E2BIG));
	if (mini_init_master(&master, env))
	{
		mini_end_of_program(&master);
		return (g_mini_errno);
	}
	ft_termios_handler(0);
	while (ft_readline(&master))
		;
	ft_termios_handler(1);
	mini_end_of_program(&master);
	return (0);
}
