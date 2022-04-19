/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export_env_test.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:01:44 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/09 11:02:10 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	display_export_env_test(t_master *master)
{
	size_t	a;
	size_t	cases;

	a = 0;
	cases = 42;
	dprintf(1, "\n\nDISPLAY EXPORT ENV BUILT INS\n\n");
	while (a <= cases)
	{
		dprintf(1, "\n");
		mini_export_built_in(master->envdata, NULL, 1);
		dprintf(1, "\n");
		mini_env_built_in(master->envdata, 1);
		dprintf(1, "\n\nCASE %zu/%zu\n\n", a, cases);
		switch (a)
		{
			case 0:
				mini_export_built_in(master->envdata, "OUAF", 1); break;
			case 1:
				mini_export_built_in(master->envdata, "OUEF=ouef", 1); break;
			case 2:
				mini_export_built_in(master->envdata, "APPEND=ouaf", 1); break;
			case 3:
				mini_export_built_in(master->envdata, "APPEND+=ouaf", 1); break;
			case 4:
				mini_export_built_in(master->envdata, "APPEND+=ouaf", 1); break;
			case 5:
				mini_export_built_in(master->envdata, "APPEND2+=ouef", 1); break;
			case 6:
				mini_export_built_in(master->envdata, "APPEND2+=ouef", 1); break;
			case 7:
				mini_export_built_in(master->envdata, "TES=T=", 1); break;
			case 8:
				mini_export_built_in(master->envdata, "TE+S=T=", 1); break;
			case 9:
				mini_export_built_in(master->envdata, "TES.T=123", 1); break;
			case 10:
				mini_export_built_in(master->envdata, "TES.T=123", 1); break;
			case 11:
				mini_export_built_in(master->envdata, "TES+T=123", 1); break;
			case 12:
				mini_export_built_in(master->envdata, "TES=T=123", 1); break;
			case 13:
				mini_export_built_in(master->envdata, "MIAOU=miaou", 1); break;
			case 14:
				mini_export_built_in(master->envdata, "MIAOU=", 1); break;
			case 15:
				mini_export_built_in(master->envdata, "MIAOU", 1); break;
			case 16:
				mini_export_built_in(master->envdata, "-TEST=123", 1); break;
			case 17:
				mini_export_built_in(master->envdata, "_TEST=123", 1); break;
			case 18:
				mini_export_built_in(master->envdata, "TES_T=123", 1); break;
			case 19:
				mini_export_built_in(master->envdata, "TEST_=123", 1); break;
			case 20:
				mini_export_built_in(master->envdata, "TE*ST=123", 1); break;
			case 21:
				mini_export_built_in(master->envdata, "TES#T=123", 1); break;
			case 22:
				mini_export_built_in(master->envdata, "TES@T=123", 1); break;
			case 23:
				mini_export_built_in(master->envdata, "TES!T=123", 1); break;
			case 24:
				mini_export_built_in(master->envdata, "TES$?T=123", 1); break;
			case 25:
				mini_export_built_in(master->envdata, "=============123", 1); break;
			case 26:
				mini_export_built_in(master->envdata, "+++++++=123", 1); break;
			case 27:
				mini_export_built_in(master->envdata, "________=123", 1); break;
			case 28:
				mini_export_built_in(master->envdata, "export", 1); break;
			case 29:
				mini_export_built_in(master->envdata, "echo", 1); break;
			case 30:
				mini_export_built_in(master->envdata, "pwd", 1); break;
			case 31:
				mini_export_built_in(master->envdata, "cd", 1); break;
			case 32:
				mini_export_built_in(master->envdata, "export", 1); break;
			case 33:
				mini_export_built_in(master->envdata, "unset", 1); break;
			case 34:
				mini_export_built_in(master->envdata, "sudo", 1); break;
			case 35:
				mini_export_built_in(master->envdata, "TES^T=123", 1); break;
			case 36:
				mini_export_built_in(master->envdata, "TES!T=123", 1); break;
			case 37:
				mini_export_built_in(master->envdata, "TEST+=100", 1); break;
			case 38:
				mini_export_built_in(master->envdata, "TE-ST=100", 1); break;
			case 39:
				mini_export_built_in(master->envdata, "-TEST=100", 1); break;
			case 40:
				mini_export_built_in(master->envdata, "TEST-=100", 1); break;
			case 41:
				mini_export_built_in(master->envdata, "_TEST=100", 1); break;
			case 42:
				mini_export_built_in(master->envdata, "PWD", 1); break;
			default:
				dprintf(1, "WTF just happened ?\n"); break;
		}
		a++;
	}
	dprintf(1, "\n");
	mini_export_built_in(master->envdata, NULL, 1);
	dprintf(1, "\n");
	mini_env_built_in(master->envdata, 1);
}
