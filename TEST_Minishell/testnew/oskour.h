/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oskour.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 10:01:47 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/25 09:34:59 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OSKOUR_H
# define OSKOUR_H

/*/////////////////////////////////////////////////////////////////////////////
		INCLUDES
*//////////////////////////////////////////////////////////////////////////////

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
	char	*content;
};

struct s_fdstruct
{
	char	*startpath;
	int		fd_in;
	int		fd_out;
	int		fd_err;
};

/*/////////////////////////////////////////////////////////////////////////////
		FUNCTION PROTOTYPES & FILES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- main.c --------------------*/

int		mini_errprint(char *str, char *file, int line, char *func);
//int	main(int ac, char **av, char **env);

/*-------------------- mini_pwd.c --------------------*/

int		mini_bi_pwd(int fd_out);

/*-------------------- mini_init.c --------------------*/

int		mini_init_envdata(t_envdata *envdata, char **env);
int		mini_init_fdstruct(t_fd *fdstruct, char **env);

/*-------------------- mini_env.c --------------------*/

void	mini_free_envlist(t_envdata *envdata);
char	**mini_get_paths(char **env);
void	mini_bi_env(t_envdata *data, int fd_out);

#endif //OSKOUR_H