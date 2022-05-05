/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:08:58 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/05 14:13:45 by ljohnson         ###   ########lyon.fr   */
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

# define IDT_CMD 10
# define IDT_BTIN 20
# define IDT_REDIR 30

# define DFI		__FILE__
# define DLI		__LINE__
# define DFU		(char *)__FUNCTION__

# define E_AC		"MINISHELL ERROR: No argument required\n"
# define E_MALLOC	"MINISHELL ERROR: Memory Allocation failed\n"

# define E_ENVDATA	"INITIALIZATION ERROR: Creation of envdata failed\n"
# define E_FDSTRUCT	"INITIALIZATION ERROR: Creation of fdstruct failed\n"

# define E_ID		"BUILT-IN ERROR: Not a valid identifier\n"
# define E_CWD		"BUILT-IN ERROR: Getcwd function failed\n"
# define E_HOME		"BUILT-IN ERROR: Home not set\n"
# define E_CHDIR	"BUILT-IN ERROR: Chdir function failed\n"
# define E_OLDPWD	"BUILT-IN ERROR: Oldpwd not set\n"
# define E_EXIT_NUM	"BUILT-IN ERROR: Exit: Numeric Argument Required\n"
# define E_EXIT_ARG	"BUILT-IN ERROR: Exit: Too Many Arguments\n"

# define E_CMD_F	"EXECUTION ERROR: Command not found\n"
# define E_CMD_X	"EXECUTION ERROR: Command execution permission denied\n"
# define E_CMD_R	"EXECUTION ERROR: Command read permission denied\n"
# define E_CMD_W	"EXECUTION ERROR: Command write permission denied\n"
# define E_EXECVE	"EXECUTION ERROR: Execve function failed\n"
# define E_DUP		"EXECUTION ERROR: Dup function failed\n"
# define E_DUP2		"EXECUTION ERROR: Dup2 function failed\n"
# define E_OPEN		"EXECUTION ERROR: Open function failed\n"
# define E_READ		"EXECUTION ERROR: Read function failed\n"
# define E_PIPE		"EXECUTION ERROR: Pipe function failed\n"
# define E_FORK		"EXECUTION ERROR: Fork function failed\n"
# define E_WRITE	"EXECUTION ERROR: Write function failed\n"
# define E_CLOSE	"EXECUTION ERROR: Close function failed\n"

# define E_FILE_F	"FD ERROR: File not found\n"
# define E_FILE_X	"FD ERROR: File execution permission denied\n"
# define E_FILE_R	"FD ERROR: File read permission denied\n"
# define E_FILE_W	"FD ERROR: File write permission denied\n"

# define E_SUPPORT	"PARSING ERROR: Characters non supported by Minishell\n"
# define E_SYNTAX	"PARSING ERROR: Syntax error near unexpected token\n"

# define W_PATH		"INITIALIZATION WARNING: PATHS not set\n"

# define W_CMD_F	"EXECUTION WARNING: Command not found\n"
# define W_CMD_X	"EXECUTION WARNING: Command execution permission denied\n"
# define W_CMD_R	"EXECUTION WARNING: Command read permission denied\n"
# define W_CMD_W	"EXECUTION WARNING: Command write permission denied\n"

# define W_FILE_F	"FD WARNING: File not found\n"
# define W_FILE_X	"FD WARNING: File execution permission denied\n"
# define W_FILE_R	"FD WARNING: File read permission denied\n"
# define W_FILE_W	"FD WARNING: File write permission denied\n"

/*/////////////////////////////////////////////////////////////////////////////
		TYPEDEF & STRUCT
*//////////////////////////////////////////////////////////////////////////////

int							g_mini_errno;
typedef struct s_master		t_master;

typedef struct s_fdstruct	t_fdstruct;

typedef struct s_envdata	t_envdata;
typedef struct s_env		t_env;

typedef struct s_execdata	t_execdata;
typedef struct s_cmd		t_cmd;

//master structure handling everything
struct s_master
{
	t_envdata	*envdata;
	t_execdata	*execdata;
	t_fdstruct	*fdstruct;
};

//main structure for fd handling
struct s_fdstruct
{
	int	fd_in;
	int	fd_out;
	int	fd_err;
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

//main structure for exec handling
struct s_execdata
{
	t_list	*lst;
	size_t	lst_size;
	void	*start;
	int		out_redir;
};

//link of execdata->lst
struct s_cmd
{
	int		token_id;
	char	*raw;
	char	**split;
	int		len_cmd;
};

/*/////////////////////////////////////////////////////////////////////////////
		INIT FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- main.c --------------------*/

int		mini_error_print(char *str, char *file, int line, char *func);
int		mini_warning_print(char *str, char *file, int line, char *func);
// int	main(int ac, char **av, char **env);

/*-------------------- init_master.c --------------------*/

int		mini_init_master(t_master *master, char **env);

/*-------------------- init_envdata.c --------------------*/

int		mini_init_paths(t_envdata *envdata);
int		mini_init_env_var(t_envdata *envdata, char *envline);
int		mini_init_base_vars(t_envdata *envdata);
int		mini_init_envdata(t_envdata *envdata, char **env);

/*-------------------- init_fdstruct.c --------------------*/

int		mini_init_fdstruct(t_fdstruct *fdstruct);

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

/*-------------------- manage_execution.c --------------------*/

char	*mini_check_cmd_paths(char **paths, char *cmd);
int		mini_exec_hub(t_master *master, t_cmd *cmd);

/*-------------------- manage_fdstruct.c --------------------*/

int		mini_reset_fdstruct(t_fdstruct *fdstruct);
int		mini_close_fdstruct(t_fdstruct *fdstruct);

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

int		mini_echo_built_in(char **split);

/*/////////////////////////////////////////////////////////////////////////////
		PARSING FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- parsing_main.c --------------------*/

int		mini_open_state_loop(char *line, char opener, int a, int len);
int		mini_check_line(char *line);

/*/////////////////////////////////////////////////////////////////////////////
		EXECUTION FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- exec_main.c --------------------*/

int		mini_execve(t_envdata *envdata, t_cmd *cmd);
int		mini_built_in_hub(t_master *master, t_cmd *cmd);
int		mini_child_process(t_master *master, t_cmd *cmd, int fd_link);
int		mini_end_of_loop(t_master *master, t_cmd *cmd, int fd_link);
int		mini_exec_loop(t_master *master, int fd_link);

/*-------------------- exec_redirection.c --------------------*/

int		mini_set_fd_in(t_cmd *cmd, int *i);
int		mini_set_fd_out(t_cmd *cmd, int i);
int		mini_redirect(int fd_in, int fd_out);
int		mini_redirection_hub(t_cmd *cmd);

/*/////////////////////////////////////////////////////////////////////////////
		END FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- end_of_program.c --------------------*/

void	mini_free_envdata_list(t_envdata *envdata);
void	mini_end_of_program(t_master *master);

/*/////////////////////////////////////////////////////////////////////////////
		TEST FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

void	mini_display_hub(t_master *master, int ac, char **av, char **env);

void	display_env_main(char **env);
void	display_env_minishell(t_master *master);
void	display_env_paths(t_master *master);
void	display_envsplit_minishell(t_master *master);
void	display_errors(void);

void	display_export_env_test(t_master *master);
//void	init_unset_test(t_master *master);
void	display_export_unset_test(t_master *master);
void	display_cd_pwd_test(t_master *master);

void	display_check_line_test(void);

//void	init_execdata_test(t_execdata *execdata, int ac, char **av);
void	display_exec_test(t_master *master, int ac, char **av);

#endif //MINISHELL_H