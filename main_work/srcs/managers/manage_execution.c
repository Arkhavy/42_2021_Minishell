/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:07:18 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/17 09:01:03 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Fait tourner chaque path avec la commande pour vérifier son existence
char	*mini_check_cmd_paths(char **paths, char *cmd)
{
	char	*tmp;
	size_t	a;

	a = 0;
	if (!cmd)
		return (NULL);
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	while (paths[a])
	{
		tmp = ft_strjoin(paths[a], cmd);
		if (!access(tmp, F_OK))
			return (tmp);
		free (tmp);
		a++;
	}
	return (NULL);
}

int	mini_exec_hub(t_master *master, t_cmd *cmd)
{
	if (cmd->token_id == IDT_CMD)
		exit (mini_execve(master->envdata, cmd));
	else if (cmd->token_id == IDT_BTIN)
		exit (mini_built_in_hub(master, cmd));
	else if (cmd->token_id == IDT_REDIR)
		exit (mini_redirection_hub(cmd));
	return (0);
}

int	mini_built_in_part_one(t_master *master, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->split[0], "echo",
			ft_get_highest(cmd->len_cmd, ft_strlen("echo"))))
		exit (mini_echo_built_in(cmd->split));
	if (!ft_strncmp(cmd->split[0], "pwd",
			ft_get_highest(cmd->len_cmd, ft_strlen("pwd"))))
		exit (mini_pwd_built_in());
	if (!ft_strncmp(cmd->split[0], "env",
			ft_get_highest(cmd->len_cmd, ft_strlen("env"))))
		exit (mini_env_built_in(master->envdata));
	if (!ft_strncmp(cmd->split[0], "exit",
			ft_get_highest(cmd->len_cmd, ft_strlen("exit"))))
		exit (0);
	if (!ft_strncmp(cmd->split[0], "cd",
			ft_get_highest(cmd->len_cmd, ft_strlen("cd"))))
		exit (mini_cd_built_in(master->envdata, cmd->split[1]));
	return (-1);
}

int	mini_built_in_part_two(t_master *master, t_cmd *cmd)
{
	int	a;

	a = 1;
	if (!ft_strncmp(cmd->split[0], "export",
			ft_get_highest(cmd->len_cmd, ft_strlen("export"))))
	{
		while (cmd->split[a])
		{
			mini_export_built_in(master->envdata, cmd->split[a]);
			a++;
		}
		exit (0);
	}
	if (!ft_strncmp(cmd->split[0], "unset",
			ft_get_highest(cmd->len_cmd, ft_strlen("unset"))))
	{
		while (cmd->split[a])
		{
			mini_unset_built_in(master->envdata, cmd->split[a]);
			a++;
		}
		exit (0);
	}
	return (-1);
}
