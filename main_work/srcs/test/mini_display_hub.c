/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_display_hub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:48:34 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/18 17:24:03 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#define BLACK "\e[1;30m"
#define RED "\e[1;31m"
#define GREEN "\e[1;32m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[1;34m"
#define PURPLE "\e[1;35m"
#define CYAN "\e[1;36m"
#define WHITE "\e[1;37m"
#define RESET "\e[0m"

void	mini_display_hub(t_master *master, int ac, char **av, char **env)
{
	// dprintf(1, "\n\n\e[1;31mDISPLAY INIT\e[0m\n\n");
	// display_errors();
	// display_env_main(env);
	// display_env_minishell(master);
	// display_envsplit_minishell(master);
	// display_env_paths(master);
	// dprintf(1, "\n\n\e[1;31mDISPLAY BUILT INS\e[0m\n\n");
	// display_export_env_test(master);
	// display_export_unset_test(master);
	// display_cd_pwd_test(master);
	// dprintf(1, "\n\n\e[1;31mDISPLAY CHECKLINE\e[0m\n\n");
	// display_check_line_test();
	(void)env;
	display_exec_test(master, ac, av);
}

//WiP export + echo
//Exit will be tested with readline, still need to make tests for it
//Indexing of env_vars in progress
//export display in progress, need indexing

//Parsing will need rework and more thoughts
//IT'S SLOWLY BUILDING WOAH
//Might need fractionned schedules to work more ?