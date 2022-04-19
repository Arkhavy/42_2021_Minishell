/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:08:58 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/17 12:54:50 by ljohnson         ###   ########lyon.fr   */
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
# define E_ENVDATA	"INITIALIZATION ERROR: Creation of envdata failed\n"
# define E_ID		"BUILT-IN ERROR: Not a valid identifier\n"
# define E_CWD		"BUILT-IN ERROR: Getcwd function failed\n"
# define E_HOME		"BUILT-IN ERROR: Home not set\n"
# define E_CHDIR	"BUILT-IN ERROR: Chdir function failed\n"
# define E_OLDPWD	"BUILT-IN ERROR: Oldpwd not set\n"
# define E_EXIT_NUM	"BUILT-IN ERROR: Exit: Numeric Argument Required\n"
# define E_EXIT_ARG	"BUILT-IN ERROR: Exit: Too Many Arguments\n"

# define E_SUPPORT	"PARSING ERROR: Characters not supported by Minishell\n"
# define E_SYNTAX	"PARSING ERROR: Syntax error near unexpected token\n"
# define E_QUOTE	"PARSING ERROR: Unclosed quotes\n"

# define W_PATH		"INITIALIZATION WARNING: PATHS not set\n"

/*/////////////////////////////////////////////////////////////////////////////
		TYPEDEF & STRUCT
*//////////////////////////////////////////////////////////////////////////////

int							g_mini_errno;
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
// int	main(int ac, char **av, char **env);

/*-------------------- mini_init_main.c --------------------*/

int		mini_init_master(t_master *master, char **env);

/*-------------------- mini_init_envdata.c --------------------*/

int		mini_init_paths(t_envdata *envdata);
int		mini_init_env_var(t_envdata *envdata, char *envline);
int		mini_init_base_vars(t_envdata *envdata);
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

/*-------------------- manage_envdata_lst.c --------------------*/

char	**mini_convert_lst_to_split(t_envdata *envdata);

/*/////////////////////////////////////////////////////////////////////////////
		BUILT_IN FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- built_in_export.c --------------------*/

int		mini_export_display(t_envdata *envdata);
// int	mini_check_raw_arg(char *raw_arg);
void	mini_add_var(t_envdata *envdata, char *arg, int append);
int		mini_export_built_in(t_envdata *envdata, char *raw_arg);

/*-------------------- built_in_unset.c --------------------*/

// int	mini_check_raw_arg(char *raw_arg);
int		mini_unset_built_in(t_envdata *envdata, char *raw_arg);

/*-------------------- built_in_env.c --------------------*/

int		mini_env_built_in(t_envdata *envdata);

/*-------------------- built_in_pwd.c --------------------*/

int		mini_pwd_built_in(void);

/*-------------------- built_in_cd.c --------------------*/

int		mini_chdir_home(t_envdata *envdata, char *path, char *old_pwd);
int		mini_chdir_oldpwd(t_envdata *envdata, char *old_pwd);
int		mini_cd_built_in(t_envdata *envdata, char *path);

/*-------------------- built_in_exit.c --------------------*/

// int	mini_check_raw_arg(char *raw_arg);
int		mini_exit_built_in(t_master *master, char *raw_arg);

/*-------------------- built_in_echo.c --------------------*/

int		mini_echo_built_in(char *raw_arg, int option);

/*/////////////////////////////////////////////////////////////////////////////
		PARSING FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- parsing_main.c --------------------*/

int		mini_loop_quote(char *line, char quote, int a);
int		mini_check_supported_char(char *line, int a);
int		mini_check_syntax(char *line, char symbol, int a);
int		mini_check_line(char *line);

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

void	display_env_main(char **env);
void	display_env_minishell(t_master *master);
void	display_env_paths(t_master *master);
void	display_envsplit_minishell(t_master *master);
void	display_errors(void);
void	mini_display_hub(t_master *master, char **env);

void	display_export_env_test(t_master *master);
//void	init_unset_test(t_master *master);
void	display_export_unset_test(t_master *master);
void	display_cd_pwd_test(t_master *master);

void	display_check_line_test(void);

#endif //MINISHELL_H