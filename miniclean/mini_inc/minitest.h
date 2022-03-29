/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitest.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:18:29 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/29 10:51:30 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITEST_H
# define MINITEST_H

# include <minishell.h>

/*-------------------- mini_display1.c --------------------*/

void	display_errors(void);
void	display_env_main(char **env);
void	display_env_minishell(t_master *master);
void	display_envsplit_minishell(t_master *master);
void	display_env_paths(t_master *master);

/*-------------------- mini_display2.c --------------------*/

void	display_export_env_test(t_master *master);

#endif //MINITEST_H