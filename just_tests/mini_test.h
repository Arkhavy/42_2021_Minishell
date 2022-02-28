/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:05:38 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/15 13:13:12 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TEST_H
# define MINI_TEST_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stddef.h>
# include <sys/wait.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include <pthread.h>

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

# include "libft/lib_includes/libft.h"

# define ERR_PIPE "ERRPX: Pipe failed"
# define ERR_CMD "ERRPX: Command not found"
# define ERR_ACCESS "ERRPX: Command permission denied"
# define ERR_FORK "ERRPX: Fork failed"
# define ERR_PATH "ERRPX: There was an error retrieving paths"
# define ERR_WAIT "ERRPX: There was an error while waiting for processes"
# define ERR_CLOSE "ERRPX: Close failed"
# define ERR_DUP "ERRPX: Dup failed"
# define ERR_EXECVE "ERRPX: Execve failed"
# define ERR_WRITE "ERRPX: Write failed"
# define ERR_READ "ERRPX: Infile read failed"
# define FILE __FILE__
# define LINE __LINE__
# define FUNC __FUNCTION__

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

char	**mini_get_paths(t_pipex pipex);
char	*mini_get_file(t_pipex pipex, char *cmd);
char	*mini_get_cmd(t_pipex pipex, char **split, int a);
void	mini_print_error(char *message, char *file, int line, char *function);

#endif //MINI_TEST_H