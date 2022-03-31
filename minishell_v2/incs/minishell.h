/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:08:58 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/31 11:45:01 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <libft.h>

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

# define DFI		__FILE__
# define DLI		__LINE__
# define DFU		(char *)__FUNCTION__
# define E_AC		"MINISHELL ERROR: No argument required\n"
# define E_MALLOC	"MINISHELL ERROR: Memory Allocation failed\n"
# define E_ENVDATA	"MINISHELL ERROR: Init of envdata failed\n"
# define E_ID		"MINISHELL ERROR: Not a valid identifier\n"

# define W_PATH		"MINISHELL WARNING: PATHS not set\n"

/*/////////////////////////////////////////////////////////////////////////////
		TYPEDEF & STRUCT
*//////////////////////////////////////////////////////////////////////////////

typedef struct s_master		t_master;
typedef struct s_envdata	t_envdata;
typedef struct s_env		t_env;

//master structure handling everything
struct s_master
{
	t_envdata	*envdata;
};

//main structure for env handling
struct s_envdata
{
	t_list	*lst;
	size_t	lst_size;
	void	*start;
	char	**paths;
};

//link of envdata->lst
struct s_env
{
	char	*name;
	char	*value;
	size_t	name_len;
	int		index;
};

/*/////////////////////////////////////////////////////////////////////////////
		INIT FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- main.c --------------------*/

int		mini_error_print(char *str, char *file, int line, char *func);
int		mini_warning_print(char *str, char *file, int line, char *func);
//int	main(int ac, char **av, char **env);

/*-------------------- mini_init_main.c --------------------*/

int		mini_init_master(t_master *master, char **env);

/*-------------------- mini_init_envdata.c --------------------*/

int		mini_init_paths(t_envdata *envdata);
int		mini_init_env_var(t_envdata *envdata, char *env);
int		mini_init_envdata(t_envdata *envdata, char **env);

/*/////////////////////////////////////////////////////////////////////////////
		MANAGERS FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- manage_envdata_vars.c --------------------*/

void	mini_delete_env_var(t_envdata *envdata, t_list *prev, t_list *current);
void	mini_append_env_var_value(t_envdata *envdata, char *name, char *value);
void	mini_change_env_var_value(t_envdata *envdata, char *name, char *value);
void	*mini_set_env_var(t_envdata *envdata, char *name, char *value);
void	*mini_get_env_var(t_envdata *envdata, char *name);

/*-------------------- manage_envdata_index.c --------------------*/

void	*mini_get_env_var_by_index(t_envdata *envdata, int index);
void	mini_reset_env_list_index(t_envdata *envdata);
void	mini_set_env_list_index(t_envdata *envdata);

/*/////////////////////////////////////////////////////////////////////////////
		BUILT_IN FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- built_in_export.c --------------------*/

int		mini_export_display(t_envdata *envdata, int fd_out);
int		mini_check_raw_arg(char *raw_arg);
void	mini_add_var(t_envdata *envdata, char *arg, int append);
int		mini_export_built_in(t_envdata *envdata, char *raw_arg, int fd_out);

/*/////////////////////////////////////////////////////////////////////////////
		PARSING FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*/////////////////////////////////////////////////////////////////////////////
		EXECUTION FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*/////////////////////////////////////////////////////////////////////////////
		END FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- end_of_program.c --------------------*/

void	mini_free_envdata_list(t_envdata *envdata);
void	mini_end_of_program(t_master *master);

/*/////////////////////////////////////////////////////////////////////////////
		TEST FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

#endif //MINISHELL_H