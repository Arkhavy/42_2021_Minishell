/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ouaf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:04:02 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/25 14:52:00 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**mini_add_slash(char **paths)
{
	char	*tmp;
	size_t	a;

	a = 0;
	tmp = NULL;
	while (paths[a])
	{
		tmp = paths[a];
		paths[a] = ft_strjoin(paths[a], "/");
		free (tmp);
		a++;
	}
	return (paths);
}

char	*mini_check_cmd(char *raw_cmd, char **paths)
{
	size_t	a;
	char	*cmd;

	a = 0;
	if (ft_int_strchr(raw_cmd, ' ') == -1)
		cmd = ft_strdup(raw_cmd);
	else
		cmd = ft_substr(raw_cmd, 0, ft_int_strchr(raw_cmd, ' '));
	if (!access(cmd, F_OK))
		return (cmd);
	while (paths[a])
	{
		cmd = ft_strfreejoin(ft_strdup(paths[a]), cmd);
		if (!access(cmd, F_OK))
			return (cmd);
		a++;
	}
	free (cmd);
	return (NULL);
}

char	*mini_get_cmd(t_envdata *envdata, char *raw_cmd)
{
	t_env	*env_var;
	char	*cmd;
	char	**paths;

	cmd = NULL;
	paths = NULL;
	env_var = mini_get_env_var(envdata, "PATH");
	if (!env_var || !env_var->value)
	{
		mini_errprint(E_PATH, DFI, DLI, DFU);
		return (NULL);
	}
	paths = mini_add_slash(ft_split(env_var->value, ':'));
	if (!paths)
	{
		mini_errprint(E_MALLOC, DFI, DLI, DFU);
		return (NULL);
	}
	cmd = mini_check_cmd(raw_cmd, paths);
	ft_free_split(paths);
	return (cmd);
}

//function might evolve over time and reflexion
int	mini_cmd_handler(t_envdata *envdata, char *raw_cmd)
{
	char	**env_split;
	char	**cmd_split;
	char	*cmd;

	env_split = NULL;
	cmd_split = NULL;
	cmd = mini_get_cmd(envdata, raw_cmd);
	if (cmd)
	{
		cmd_split = ft_split(raw_cmd, ' ');
		if (access(cmd, X_OK) == -1)
			return (mini_errprint(E_ACCESS_X, DFI, DLI, DFU));
		env_split = mini_linked_to_split(envdata->lst, envdata->lst_size);
		if (execve(cmd, cmd_split, env_split) == -1)
			return (mini_errprint(E_EXECVE, DFI, DLI, DFU));
		ft_free_split(env_split);
		ft_free_split(cmd_split);
		free (cmd);
		return (0);
	}
	free (cmd);
	return (-1);
}

int	mini_pipex(t_master *master)
{
	int		pipe_fd[2];
	pid_t	pid;
	size_t	a;

	a = 0;
	if (pipe(pipe_fd) == -1)
		return (mini_errprint(E_PIPE, DFI, DLI, DFU));
	pid = fork();
	if (pid == -1)
		return (mini_errprint(E_FORK, DFI, DLI, DFU));
	else if (pid == 0)
	{
		if (dup2(pipe_fd[1], STDIN_FILENO) == -1)
			return (mini_errprint(E_DUP, DFI, DLI, DFU));
		if (dup2(pipe_fd[0], STDOUT_FILENO) == -1)
			return (mini_errprint(E_DUP, DFI, DLI, DFU));
		if (mini_cmd_handler(master->envdata, master->ouaf->raw_cmd) == -1) //
			return (mini_errprint(E_HANDLER, DFI, DLI, DFU));
		//boucle cmd_handler ? il faut un troisième fd relai voire une fonction pour ça
	}
}

int	mini_execution(t_master *master)
{
	
	return (0);
}















/*
Besoin d'une fonction appelant cmd_handler
	Cette fonction est probablement celle appelant fork / pipe / dup
	probablement celle qui va boucler selon le nombre de pipe
	jusqu'à la première redirection rencontrée
*/

/*
Le fonctionnement des pipes et dup vont être assez différents de pipex
	la différence principale est qu'on peut afficher dans le terminal
	il nous faut donc garder les fd de départ
	si pipe de sortie / redirection, récupérer l'output
	si aucun des deux, laisser le fd sur 1
		récupérer les fd de terminaux dès le départ est donc une idée
	s'il y a beaucoup de commandes, il nous faut pouvoir alterner les fd
		sans foutre la merde dans le programme
			revoir le fonctionnement de pipe histoire d'être sûr
			les close seront importants, cat /dev/urandom | head -c10 doit fonctionner
*/

/*
Pré-parsing
Potentielle fonction expand pour aller chercher les variables environnement
built_in	cd
	possède un argument, pas d'option
	retire les quotes, chdir s'occupe du reste
built_in	echo
	possède une option, possède un argument
	retire les quotes par paire mais pas leur contenu
built_in	env
	pas d'argument, pas d'option
	si un argument est présent, renvoyer une erreur
built_in	exit
	possède un argument, pas d'option
	l'argument doit être un int, négatif ou non, qui n'est pas hors limite long int
	retire les quotes par paire
built_in	export
	possède un argument, pas d'option
	retire les quotes par paire
built_in	unset
	possède un argument, pas d'option
	retire les quotes par paire
built_in	pwd
	pas d'argument, pas d'option
	si un argument est présent, s'en débarasser, il sert à rien
*/

/*
exec
pipex

fd_in
fd_out
(<command> [option] [arg]) = one char *
env needed for execve
path needed for command
if path not set
	getenv ?
	or error and don't work ?
	does getenv(PATH) works even when the var is unset ? return NULL
	is it ok to set paths by hand if not set ? bad idea
	relative paths will not work, absolute paths will work unless access is denied
else
	pipex_bonus work++ -> need to have a pipe/dup handler or something similar

get_path -> ce sera un check depuis la liste chaînée,
pas de problème concernant strncmp vu qu'il ne sera pas utilisé
split des paths de toute façon juste après
	
	env_var = mini_get_env_var(envdata, "PATH");
	if (!env_var)
		mini_errprint(E_PATH, DFI, DLI, DFU); //error : path not set ?
	else
	paths = ft_split(env_var->value, ':');
	if (!check_cmd(cmd, paths))
		access(X_OK)
		env_split = mini_linked_to_split(envdata->lst);
		execve(cmd, paths, env_split);
	else
		mini_errprint(E_CMD, DFI, DLI, DFU); //error : command not found
		exit child
*/

/*
PEER TO PEER
machine à état pour le parsing
parsing until pipe
struct s_machine
{
	bool	s_quote;
	bool	d_quote;
	bool	dollars;
	bool	word;
	char	*redirection; ?
	bool	pipe; ?
}
linked list, each link is a command between pipes
need to think about redirections
*/