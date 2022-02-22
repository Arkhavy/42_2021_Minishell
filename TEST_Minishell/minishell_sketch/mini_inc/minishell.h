/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 12:48:53 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/17 12:26:21 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**
 * stdlib.h
 * unistd.h
 * limits.h
 * fcntl.h
 * stdarg.h
 * stddef.h
 * sys/wait.h
 * stdio.h
 * math.h
 * sys/time.h
 * pthread.h
*/
# include "libft.h"

# include <string.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>

/*/////////////////////////////////////////////////////////////////////////////
		DEFINES
*//////////////////////////////////////////////////////////////////////////////

# define ERR_PIPE "ERROR: Pipe failed"
# define ERR_CMD "ERROR: Command not found"
# define ERR_ACCESS "ERROR: Command permission denied"
# define ERR_FORK "ERROR: Fork failed"
# define ERR_PATH "ERROR: There was an error retrieving paths"
# define ERR_WAIT "ERROR: There was an error while waiting for processes"
# define ERR_CLOSE "ERROR: Close failed"
# define ERR_DUP "ERROR: Dup failed"
# define ERR_EXECVE "ERROR: Execve failed"
# define ERR_WRITE "ERROR: Write failed"
# define ERR_READ "ERROR: Infile read failed"
# define ERR_AC "ERROR: There should be no argument while starting Minishell"
# define FILE __FILE__
# define LINE __LINE__
# define FUNC __FUNCTION__

/*/////////////////////////////////////////////////////////////////////////////
		STRUCTURES
*//////////////////////////////////////////////////////////////////////////////

typedef struct s_pipex	t_pipex;

struct s_pipex
{
	int		ac;
	char	**av;
	char	**env;
	char	**env_paths;
	char	**cmd_split;
	char	*cmd;
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];
	pid_t	pid;
};

/*/////////////////////////////////////////////////////////////////////////////
		ALL FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- minishell.c --------------------*/

int		mini_print_error(char *message, char *file, int line, char *function);
//int	main(int ac, char **av, char **env);

/*-------------------- mini_command_checker.c --------------------*/

char	**mini_get_paths(t_pipex pipex);
//char	*mini_get_file(t_pipex pipex, char *cmd);
char	*mini_get_cmd(t_pipex pipex, char **split, int a);
//char	*mini_get_cmd(t_pipex pipex, char *rawcmd); alt version

#endif //MINISHELL_H