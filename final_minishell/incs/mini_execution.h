/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execution.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 08:00:13 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/15 09:05:12 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_EXECUTION_H
# define MINI_EXECUTION_H

# include <minishell.h>
# include <mini_built_in.h>
# include <mini_defines.h>
# include <mini_init.h>
# include <mini_managers.h>
# include <mini_parsing.h>
# include <mini_prompt.h>
# include <mini_structs.h>

/*/////////////////////////////////////////////////////////////////////////////
		EXECUTION FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- exec_main.c --------------------*/

int	mini_execve(t_envdata *envdata, t_cmd *cmd);
int	mini_built_in_hub(t_master *master, t_cmd *cmd);
int	mini_child_process(t_master *master, t_cmd *cmd, int fd_link);
int	mini_end_of_loop(t_master *master, t_cmd *cmd, int fd_link);
int	mini_exec_loop(t_master *master, int fd_link);

/*-------------------- exec_redirection.c --------------------*/

int	mini_set_fd_in(t_cmd *cmd, int *i);
int	mini_set_fd_out(t_cmd *cmd, int i);
int	mini_redirect(int fd_in, int fd_out);
int	mini_redirection_hub(t_cmd *cmd);

#endif //MINI_EXECUTION_H