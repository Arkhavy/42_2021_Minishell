/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_test.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:12:45 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/16 13:12:10 by ljohnson         ###   ########lyon.fr   */
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

# include "mini_built_in.h"
# include "mini_error_def.h"

# include <string.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>

/*/////////////////////////////////////////////////////////////////////////////
		TYPEDEF & STRUCT
*//////////////////////////////////////////////////////////////////////////////

// typedef struct s_master		t_master;
typedef struct s_envdata	t_envdata;
typedef struct s_env		t_env;
// typedef struct s_fdstruct	t_fd;

// struct s_master
// {
// 	t_envdata	*envdata;
// 	// t_fd		*fdstruct;
// };

struct s_envdata
{
	t_list	*lst;
	size_t	lst_size;
	void	*start;
	char	**path;
	char	**envmain;
};

struct s_env
{
	char	*name;
	char	*value;
};

// struct s_fdstruct
// {
// 	char	*startpath;
// 	int		fd_in;
// 	int		fd_out;
// 	int		fd_err;
// };

/*/////////////////////////////////////////////////////////////////////////////
		PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- mini_env_manager.c --------------------*/

void	mini_free_envlist(t_envdata *envdata);
void	mini_delete_env_var(t_envdata *envdata, t_list *prev, t_list *current);
void	mini_set_new_value(t_envdata *envdata, char *varname, char *value);
void	*mini_get_env_var(t_envdata *envdata, char *varname);
void	*mini_set_env_var(t_envdata *envdata, char *varname, char *value);

#endif //MINISHELL_TEST_H