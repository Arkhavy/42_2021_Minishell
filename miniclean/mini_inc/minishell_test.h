/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_test.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:12:45 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/20 10:27:13 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TEST_H
# define MINISHELL_TEST_H

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
# include "libft.h"

# include <string.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>

/*/////////////////////////////////////////////////////////////////////////////
		DEFINES
*//////////////////////////////////////////////////////////////////////////////

# define E_AC		"MINISHELL ERROR: No argument required\n"
# define E_INIT		"MINISHELL ERROR: Minishell initialisation failed\n"
# define E_MALLOC	"MINISHELL ERROR: Memory Allocation failed\n"
# define E_PIPE		"MINISHELL ERROR: Pipe function failed\n"
# define E_FORK		"MINISHELL ERROR: Fork function failed\n"
# define E_DUP		"MINISHELL ERROR: Dup function failed\n"
# define E_ACCESS_F	"MINISHELL ERROR: Could not find file\n"
# define E_ACCESS_R	"MINISHELL ERROR: Could not read file\n"
# define E_ACCESS_W	"MINISHELL ERROR: Could not write on file\n"
# define E_ACCESS_X	"MINISHELL ERROR: Could not execute file\n"
# define E_EXECVE	"MINISHELL ERROR: Execve function failed\n"
# define E_OPEN		"MINISHELL ERROR: Open function failed\n"
# define E_READ		"MINISHELL ERROR: Read function failed\n"
# define E_WRITE	"MINISHELL ERROR: Write function failed\n"
# define E_CLOSE	"MINISHELL ERROR: Close function failed\n"
# define E_HOME		"MINISHELL ERROR: Home not set\n"
# define E_CHDIR	"MINISHELL ERROR: Chdir function failed\n"
# define E_PARSE	"MINISHELL ERROR: Argument parsing failed\n"
# define E_ID		"MINISHELL ERROR: Not a valid identifier\n"
# define E_CWD		"MINISHELL ERROR: Getcwd function failed\n"
# define DFI		__FILE__
# define DLI		__LINE__
# define DFU		(char *)__FUNCTION__

/*/////////////////////////////////////////////////////////////////////////////
		TYPEDEF & STRUCT
*//////////////////////////////////////////////////////////////////////////////

typedef struct s_master		t_master;
typedef struct s_envdata	t_envdata;
typedef struct s_env		t_env;
typedef struct s_fdstruct	t_fd;
typedef struct s_token		t_token;

struct s_master
{
	t_envdata	*envdata;
	t_fd		*fdstruct;
	t_token		*token;
	size_t		nb_tok;
	char		*line;
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

struct s_token
{
	int		fd_in;
	int		fd_out;
	char	*cmd;
	char	*path;
};

/*/////////////////////////////////////////////////////////////////////////////
		FUNCTION PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- minishell.c --------------------*/

void		mini_end_of_program(t_master *master);
int			mini_errprint(char *str, char *file, int line, char *func);
//int		main(int ac, char **av, char **env);

/*-------------------- mini_init.c --------------------*/

int			mini_init_master(t_master *master, char **env);
int			mini_init_envdata(t_envdata *envdata, char **env);
int			mini_init_fdstruct(t_fd *fdstruct);
//size_t	nb_pipe(char *line);
int			mini_init_token(t_master *master);

/*-------------------- mini_env_manager.c --------------------*/

void		mini_free_envlist(t_envdata *envdata);
void		mini_del_env_var(t_envdata *envdata, t_list *prev, t_list *current);
void		mini_set_new_value(t_envdata *envdata, char *varname, char *value);
void		*mini_get_env_var(t_envdata *envdata, char *varname);
void		*mini_set_env_var(t_envdata *envdata, char *varname, char *value);

/*-------------------- mini_workers.c --------------------*/

char		**mini_get_paths(char **env);

/*/////////////////////////////////////////////////////////////////////////////
		BUILT_IN PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- built_in_cd.c --------------------*/

int			mini_cd_built_in(t_envdata *envdata, char *path);

/*-------------------- built_in_export.c --------------------*/

int			mini_export_display(t_envdata *envdata, int fd_out);
void		mini_add_var(t_envdata *envdata, char *raw_arg, int append);
int			mini_check_raw_arg(char *raw_arg);
int			mini_export_built_in(t_envdata *envdata, char *raw_arg, int fd_out);

/*-------------------- built_in_unset.c --------------------*/

int			mini_unset_built_in(t_envdata *envdata, char *varname);

/*-------------------- built_in_pwd.c --------------------*/

int			mini_pwd_built_in(int fd_out);

/*-------------------- built_in_env.c --------------------*/

char		**mini_linked_to_split(t_list *lst, size_t lst_size);
int			mini_env_built_in(t_envdata *envdata, int fd_out);

/*-------------------- built_in_echo.c --------------------*/

int			mini_echo_built_in(char *arg, int option, int fd_out);

#endif //MINISHELL_TEST_H