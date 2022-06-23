/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_prompt.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 08:01:29 by ljohnson          #+#    #+#             */
/*   Updated: 2022/06/23 08:46:41 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PROMPT_H
# define MINI_PROMPT_H

# include <minishell.h>
# include <mini_built_in.h>
# include <mini_defines.h>
# include <mini_execution.h>
# include <mini_init.h>
# include <mini_managers.h>
# include <mini_parsing.h>
# include <mini_structs.h>

/*/////////////////////////////////////////////////////////////////////////////
		PROMPT FUNCTIONS PROTOTYPES
*//////////////////////////////////////////////////////////////////////////////

/*-------------------- prompt_heredoc.c --------------------*/

void	handler_here(int byte);
int		mini_check_limiter(char *prompt, char *limiter);
int		mini_heredoc(char *limiter, t_master *master);
int		ft_strlen_char(char *str, char c, int start);
void	do_after_limiter(char *str);
char	*check_var(t_master *master, char *str);

int		start_heredoc(char *limiter, t_master *master);

/*-------------------- prompt_readline.c --------------------*/

// void	case_readline(int i, char *dest, char *s1, t_master *master);
void	readline_exec(char *str, t_master *master);
int		ft_readline(t_master *master);

/*-------------------- prompt_signal.c --------------------*/

void	ft_termios_handler(int end);
void	handler(int byte);
void	search_signal(void);
void	search_signal_heredoc(void);
void	handler_here(int byte);
void	handler_child(void);

void	check_str_empty(char *str);
void	check_exit_str(t_master *master);

#endif //MINI_PROMPT_H
