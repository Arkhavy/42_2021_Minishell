/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parsing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 08:01:08 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/21 07:53:08 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PARSING_H
# define MINI_PARSING_H

# include <minishell.h>
# include <mini_built_in.h>
# include <mini_defines.h>
# include <mini_execution.h>
# include <mini_init.h>
# include <mini_managers.h>
# include <mini_prompt.h>
# include <mini_structs.h>

/*/////////////////////////////////////////////////////////////////////////////
		PARSING FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- parsing_heredoc.c --------------------*/

char	*check_char(char *line);

/*-------------------- parsing_main.c --------------------*/

int		mini_loop_quote(char *line, char quote, int a);
int		mini_check_supported_char(char *line, int a);
int		mini_check_syntax(char *line, char symbol, int a);
int		mini_check_line(char *line);

/*-------------------- parsing_test.c --------------------*/

int		parsing_var(char *str);
int		parsing_pipe(char *str);
int		check_builtin(char *split, int len_cmd);
int		check_token_id(char *split, int len_cmd);
int		init_cmd(char *str, char *dest, t_master *master);

char	**split_redir(char *dest, t_cmd *cmd);
char	**split_exit(char *str, char *dest, t_cmd *cmd);
char	**split_unset(char *str, t_cmd *cmd);
char	**split_export(char *str, char *dest, t_cmd *cmd);
char	**split_env(char *dest, t_cmd *cmd);
char	**split_pwd(char *dest, t_cmd *cmd);
char	**split_cd(char *str, char *dest, t_cmd *cmd);
char	**split_echo(char *str, char *dest, t_cmd *cmd);
int		check_builtin(char *split, int len_cmd);
int		echo_n(char *str, int i);
int		pre_sort(char *str, t_master *master);
int		check_token_id(char *split, int len_cmd);
char	*put_without_d_q(char *str, char *split, int len);
int		count_arg_echo(char *str);
int		pipe_check(char *str, char *dest, int *tab_index, t_master *master);
int		redir_check(char *str, char *dest, int *tab_index, t_master *master);
int		end_check(char *str, char *dest, int *tab_index, t_master *master);
char	*un_double_quote(char *str);

char	**redir_alone(char *str, t_cmd *cmd);
char	**redir_double(char *str, t_cmd *cmd);
char	**redir_ampersand(char *str, t_cmd *cmd);
char	**redir_fd(char *str, t_cmd *cmd);
char	**redir_double_fd(char *str, t_cmd *cmd);
char	**redir_fd_ampersand(char *str, t_cmd *cmd);
int		base_fd(char str);
char	**find_case(char *str, t_cmd *cmd);
char	*test_split(char *split, char *str, int *tab_index);
int		*next_arg(char *str, int *tab_index, char c);
int		*init_tab_index(void);
int		*next_arg_base_fd(int *tab_index, char *str);
int		check_redir(char *str, char *dest, int *tab_index, t_master *master);

#endif //MINI_PARSING_H
