/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:04:10 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/16 08:32:41 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Exécute la commande donnée, valide ou non
int	mini_execve(t_envdata *envdata, t_cmd *cmd)
{
	char	*fullcmd;
	char	**envsplit;

	envsplit = NULL;
	fullcmd = mini_check_cmd_paths(envdata->paths, cmd->split[0]);
	if (!fullcmd)
		return (mini_error(ENOENT) * -1);
	if (access(fullcmd, X_OK) == -1)
	{
		free (fullcmd);
		return (mini_error(EACCES) * -1);
	}
	envsplit = mini_convert_lst_to_split(envdata);
	execve(fullcmd, cmd->split, envsplit);
	free (fullcmd);
	ft_free_split(envsplit);
	return (mini_error(EPERM) * -1);
}

int	mini_built_in_hub(t_master *master, t_cmd *cmd)
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
		exit (mini_exit_built_in(master, cmd->split[1]));
	if (!ft_strncmp(cmd->split[0], "export",
			ft_get_highest(cmd->len_cmd, ft_strlen("export"))))
		exit (mini_export_built_in(master->envdata, cmd->split[1]));
	if (!ft_strncmp(cmd->split[0], "unset",
			ft_get_highest(cmd->len_cmd, ft_strlen("unset"))))
		exit (mini_unset_built_in(master->envdata, cmd->split[1]));
	if (!ft_strncmp(cmd->split[0], "cd",
			ft_get_highest(cmd->len_cmd, ft_strlen("cd"))))
		exit (mini_cd_built_in(master->envdata, cmd->split[1]));
	return (-1);
}

int	mini_child_process(t_master *master, t_cmd *cmd, int fd_link)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (mini_error(EPIPE) * -1);
	pid = fork();
	if (pid == -1)
		return (mini_error(ENOMEM) * -1);
	else if (!pid)
	{
		if (close(pipe_fd[0]) == -1)
			return (mini_error(EBADF) * -1);
		if (dup2(fd_link, STDIN_FILENO) == -1)
			return (mini_error(EBADF) * -1);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			return (mini_error(EBADF) * -1);
		if (mini_exec_hub(master, cmd) == -1)
			return (-1);
	}
	if (close(pipe_fd[1]) == -1)
		return (mini_error(EBADF) * -1);
	if (close(fd_link) == -1)
		return (mini_error(EBADF) * -1);
	return (pipe_fd[0]);
}

int	mini_end_of_loop(t_master *master, t_cmd *cmd, int fd_link)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (mini_error(ENOMEM) * -1);
	else if (!pid)
	{
		if (dup2(fd_link, STDIN_FILENO) == -1)
			return (mini_error(EBADF) * -1);
		if (dup2(master->fdstruct->fd_out, STDOUT_FILENO) == -1)
			return (mini_error(EBADF) * -1);
		if (mini_exec_hub(master, cmd) == -1)
			return (-1);
	}
	return (fd_link);
}

int	mini_exec_loop(t_master *master, int fd_link)
{
	t_cmd	*cmd;
	size_t	a;

	a = 0;
	master->execdata->lst = master->execdata->start;
	while (master->execdata->lst)
	{
		cmd = master->execdata->lst->content;
		if (!master->execdata->lst->next && !master->execdata->out_redir)
			fd_link = mini_end_of_loop(master, cmd, fd_link);
		else
			fd_link = mini_child_process(master, cmd, fd_link);
		if (fd_link == -1)
			return (1);
		master->execdata->lst = master->execdata->lst->next;
	}
	if (close(fd_link) == -1)
		return (mini_error(EBADF));
	while (a < master->execdata->lst_size)
	{
		waitpid(-1, NULL, 0);
		a++;
	}
	mini_reset_fdstruct(master->fdstruct);
	return (0);
}

//besoin de coder la sortie de boucle
	//terminal par défaut
	//ou redirection si présente
	//need parsing
	//need réflexion sur les redirections
	//est-ce que tout fonctionne ???
	//oskour cerveau rip
//besoin de boucler sur les built-in si nécessaire
