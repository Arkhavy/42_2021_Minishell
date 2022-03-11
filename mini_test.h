/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:05:38 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/11 12:24:07 by ljohnson         ###   ########lyon.fr   */
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

# define ERR_DEF "Cette erreur n'est pas encore définie"
# define ERR_AC "ERROR: There should be no argument while starting Minishell"
# define ERR_DUP "ERROR: File Descriptor duplication failed"
# define ERR_MALLOC "ERROR: Memory Allocation failed"
# define ERR_CWD "ERROR: Could not find current working directory"
# define ERR_CMD "ERROR: Could not find command"
# define ERR_EX "ERROR: Could not execute command"
# define ERR_EXC "ERROR: There was a problem executing command"
# define ERR_PIPE "ERROR: Could not allocate Pipe File Descriptors"
# define ERR_FORK "ERROR: Fork failed"
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

/*-------------------- main.c --------------------*/

int		mini_errprint(char *str, char *file, int line, char *func);

/*-------------------- working_functions.c --------------------*/

char	**mini_get_paths(char **env);
void	mini_free_envlist(t_envdata *envdata);
int		mini_init_fdstruct(t_fd	*fdstruct, char **env);
int		mini_init_envdata(t_envdata *envdata, char **env);
char	**mini_linked_to_split(t_list *lst, size_t lst_size);
void	mini_end_of_program(t_master *master);

/*-------------------- mini_export_built_in.c --------------------*/

int		mini_check_var_name(t_envdata *envdata, char *varname);
void	mini_export_display(t_envdata *envdata, int fd_out);
void	mini_replace_var(t_envdata *envdata, char *newvar, t_env *env_var);
void	mini_add_var(t_envdata *envdata, char *newvar, t_env *env_var);
int		mini_export_built_in(t_envdata *envdata, char *newvar, int fd_out);

/*-------------------- mini_unset_built_in.c --------------------*/

int		mini_delete_var(t_list *previous, t_list *current, t_envdata *envdata);
int		mini_unset_built_in(t_envdata *envdata, char *varname);

/*-------------------- mini_pwd_built_in.c --------------------*/

int		mini_pwd_built_in(t_envdata *envdata, int fd_out);

#endif //MINI_TEST_H