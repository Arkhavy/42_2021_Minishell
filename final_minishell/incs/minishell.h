/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:58:36 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/07 13:13:12 by ljohnson         ###   ########lyon.fr   */
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

# define E_AC	"MINISHELL ERROR: No argument required\n"
# define N_AC	1

# define E_MALLOC	"MINISHELL ERROR: Memory allocation failed\n"
# define N_MALLOC	2

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

void	mini_end_of_program(t_master *master);
int		mini_error(char *str, char *arg, int err_id, int warning);
// int		main(int ac, char **av, char **env);

#endif //MINISHELL_H