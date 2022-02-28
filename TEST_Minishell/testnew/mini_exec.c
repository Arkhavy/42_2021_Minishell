/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 09:26:45 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/28 09:02:13 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "oskour.h"

//Vérifie chaque PATH pour trouver la commande si celle-ci existe
char	*mini_get_file(t_envdata envdata, char *cmd)
{
	size_t	a;
	char	*tmp;
	char	*file;

	a = 0;
	file = NULL;
	while (envdata.paths[a])
	{
		tmp = file;
		file = ft_strjoin(envdata.paths[a], cmd);
		free (tmp);
		if (!access (file, F_OK))
			break ;
		a++;
	}
	if (access(file, F_OK) == -1)
	{
		free (file);
		mini_errprint(ERR_CMD, DFI, DLI, DFU);
		return (ft_strdup(cmd));
	}
	return (file);
}

//Récupère la commande donnée sans ses flags pour vérifier son existence
char	*mini_get_cmd(t_envdata envdata, char *rawcmd)
{
	char	*cmd;
	char	*file;

	if (ft_int_strchr(rawcmd, ' ') > -1)
		cmd = ft_substr(rawcmd, 0, ft_int_strchr(rawcmd, ' '));
	else
		cmd = ft_strdup(rawcmd);
	if (!access(cmd, F_OK))
		return (cmd);
	file = mini_get_file(envdata, cmd);
	free (cmd);
	return (file);
}

//conversion de la linked list en split pour execution
char	**mini_linked_to_split(t_list *lst, size_t lst_size)
{
	t_env	*link;
	char	**split;
	char	*tmp;
	size_t	a;

	a = 0;
	split = malloc(sizeof(char *) * (lst_size + 1));
	if (!split)
		return (NULL);
	while (a < lst_size && lst)
	{
		link = lst->content;
		split[a] = ft_strjoin(link->name, "=");
		tmp = split[a];
		split[a] = ft_strjoin(split[a], link->value);
		free (tmp);
		lst = lst->next;
		a++;
	}
	split[a] = NULL;
	return (split);
}

//Fork pour pouvoir utiliser execve sur la commande donnée
//Lis fd_in, écris sur fd_out, fonctionnement sujet à changement
int	mini_exec_cmd(t_envdata envdata, int fd_in, int fd_out, char *rawcmd)
{
	pid_t	pid;
	char	*cmd;
	char	**flag;
	char	**envsplit;

	pid = fork();
	if (pid == -1)
		mini_errprint(ERR_FORK, DFI, DLI, DFU);
	else if (!pid)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			mini_errprint(ERR_DUP, DFI, DLI, DFU);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			mini_errprint(ERR_DUP, DFI, DLI, DFU);
		cmd = mini_get_cmd(envdata, rawcmd);
		if (access(cmd, X_OK) == -1)
			mini_errprint(ERR_EX, DFI, DLI, DFU);
		flag = ft_split(rawcmd, ' ');
		envsplit = mini_linked_to_split(envdata.start, envdata.lst_size);
		if (execve(cmd, flag, envsplit) == -1)
			mini_errprint(ERR_EXC, DFI, DLI, DFU);
	}
	close (fd_in);
	ft_free_split(envsplit);
	return (fd_out);
}
