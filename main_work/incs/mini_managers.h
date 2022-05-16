/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_managers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 08:00:50 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/08 11:08:07 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_MANAGERS_H
# define MINI_MANAGERS_H

# include <minishell.h>
# include <mini_built_in.h>
# include <mini_defines.h>
# include <mini_execution.h>
# include <mini_init.h>
# include <mini_parsing.h>
# include <mini_prompt.h>
# include <mini_structs.h>

/*/////////////////////////////////////////////////////////////////////////////
		MANAGERS FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- manage_envdata_lst.c --------------------*/

void	*mini_get_env_var_by_index(t_envdata *envdata, int index);
void	mini_reset_env_list_index(t_envdata *envdata);
void	mini_set_env_list_index(t_envdata *envdata);
char	**mini_convert_lst_to_split(t_envdata *envdata);

/*-------------------- manage_envdata_vars.c --------------------*/

void	mini_delete_env_var(t_envdata *envdata, t_list *prev, t_list *current);
void	mini_append_env_var_value(t_envdata *envdata, char *name, char *value);
void	mini_change_env_var_value(t_envdata *envdata, char *name, char *value);
void	*mini_set_env_var(t_envdata *envdata, char *name, char *value);
void	*mini_get_env_var(t_envdata *envdata, char *name);

/*-------------------- manage_execution.c --------------------*/

char	*mini_check_cmd_paths(char **paths, char *cmd);
int		mini_exec_hub(t_master *master, t_cmd *cmd);

#endif //MINI_MANAGERS_H