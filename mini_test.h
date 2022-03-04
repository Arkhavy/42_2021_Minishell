/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:05:38 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/04 10:46:38 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TEST_H
# define MINI_TEST_H

/*/////////////////////////////////////////////////////////////////////////////
		INCLUDES
*//////////////////////////////////////////////////////////////////////////////

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
# include "libft/lib_includes/libft.h"

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

# define ERR_DEF "\033[31m\033[1mCette erreur n'est pas encore définie\033[0m"
# define ERR_AC "\033[31m\033[1mERROR: There should be no argument while starting Minishell\033[0m"
# define ERR_DUP "\033[31m\033[1mERROR: File Descriptor duplication failed\033[0m"
# define ERR_MALLOC "\033[31m\033[1mERROR: Memory Allocation failed\033[0m"
# define ERR_CWD "\033[31m\033[1mERROR: Could not find current working directory\033[0m"
# define ERR_CMD "\033[31m\033[1mERROR: Could not find command\033[0m"
# define ERR_EX "\033[31m\033[1mERROR: Could not execute command\033[0m"
# define ERR_EXC "\033[31m\033[1mERROR: There was a problem executing command\033[0m"
# define ERR_PIPE "\033[31m\033[1mERROR: Could not allocate Pipe File Descriptors\033[0m"
# define ERR_FORK "\033[31m\033[1mERROR: Fork failed\033[0m"
# define DFI __FILE__
# define DLI __LINE__
# define DFU (char *)__FUNCTION__

/*/////////////////////////////////////////////////////////////////////////////
		TYPEDEF & STRUCTS
*//////////////////////////////////////////////////////////////////////////////

typedef struct s_master		t_master;
typedef struct s_envdata	t_envdata;
typedef struct s_env		t_env;
typedef struct s_fdstruct	t_fd;

struct s_master
{
	t_envdata	*envdata;
	t_fd		*fdstruct;
};

struct s_envdata
{
	t_list	*lst;
	size_t	lst_size;
	void	*start;
	char	**paths;
	char	**envmain;
};

struct s_env
{
	char	*name;
	char	*value;
};

struct s_fdstruct
{
	char	*startpath;
	int		fd_in;
	int		fd_out;
	int		fd_err;
};

int		mini_errprint(char *str, char *file, int line, char *func);
char	**mini_get_paths(char **env);
void	mini_free_envlist(t_envdata *envdata);
int		mini_init_fdstruct(t_fd	*fdstruct, char **env);
int		mini_init_envdata(t_envdata *envdata, char **env);
char	**mini_linked_to_split(t_list *lst, size_t lst_size);
void	mini_end_of_program(t_master *master);

#endif //MINI_TEST_H