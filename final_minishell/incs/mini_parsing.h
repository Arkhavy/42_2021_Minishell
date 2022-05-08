/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parsing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 08:01:08 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/08 11:02:48 by ljohnson         ###   ########lyon.fr   */
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
void	init_cmd(char *str, char *dest, t_master *master);

int		pre_sort(char *str, t_master *master);

#endif //MINI_PARSING_H