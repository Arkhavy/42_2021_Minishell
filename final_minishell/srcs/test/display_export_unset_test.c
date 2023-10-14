/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export_unset_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:02:27 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/06 15:18:52 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	init_unset_test(t_master *master)
{
	mini_export_built_in(master->envdata, "NOVALUE1");
	mini_export_built_in(master->envdata, "NOVALUE2");
	mini_export_built_in(master->envdata, "NOVALUE3");
	mini_export_built_in(master->envdata, "VALUE1=value");
	mini_export_built_in(master->envdata, "VALUE2=value2");
	mini_export_built_in(master->envdata, "VALUE3=value3");
	mini_export_built_in(master->envdata, "VOIDVALUE1=");
	mini_export_built_in(master->envdata, "VOIDVALUE2=");
	mini_export_built_in(master->envdata, "VOIDVALUE3=");
	mini_export_built_in(master->envdata, "APPEND1=one");
	mini_export_built_in(master->envdata, "APPEND1+= two");
	mini_export_built_in(master->envdata, "APPEND1+= three");
	mini_export_built_in(master->envdata, "APPEND2+=one");
	mini_export_built_in(master->envdata, "APPEND2+= two");
	mini_export_built_in(master->envdata, "APPEND2+= three");
	mini_export_built_in(master->envdata, "CHANGE_VALUE=one");
	mini_export_built_in(master->envdata, "CHANGE_VALUE=two");
	mini_export_built_in(master->envdata, "CHANGE_VALUE=three");
}

void	display_export_unset_test(t_master *master)
{
	size_t	a;
	size_t	cases;

	a = 0;
	cases = 42;
	dprintf(1, "\n\nDISPLAY EXPORT UNSET BUILT INS\n\n");
	init_unset_test(master);
	while (a <= cases)
	{
		dprintf(1, "\n");
		mini_export_built_in(master->envdata, NULL);
		dprintf(1, "\n");
		mini_env_built_in(master->envdata);
		dprintf(1, "\n\nCASE %zu/%zu\n\n", a, cases);
		switch (a)
		{
			case 0:
				mini_unset_built_in(master->envdata, "NOVALUE1"); break;
			case 1:
				mini_unset_built_in(master->envdata, "NOVALUE2"); break;
			case 2:
				mini_unset_built_in(master->envdata, "NOVALUE3"); break;
			case 3:
				mini_unset_built_in(master->envdata, "NOVALUE4"); break;
			case 4:
				mini_unset_built_in(master->envdata, "VALUE1"); break;
			case 5:
				mini_unset_built_in(master->envdata, "VALUE2"); break;
			case 6:
				mini_unset_built_in(master->envdata, "VALUE3"); break;
			case 7:
				mini_unset_built_in(master->envdata, "VOIDVALUE1"); break;
			case 8:
				mini_unset_built_in(master->envdata, "VOIDVALUE2"); break;
			case 9:
				mini_unset_built_in(master->envdata, "VOIDVALUE3"); break;
			case 10:
				mini_unset_built_in(master->envdata, "VOIDVALUE4"); break;
			case 11:
				mini_unset_built_in(master->envdata, "APPEND1"); break;
			case 12:
				mini_unset_built_in(master->envdata, "APPEND1"); break;
			case 13:
				mini_unset_built_in(master->envdata, "APPEND2"); break;
			case 14:
				mini_unset_built_in(master->envdata, "APPEND2"); break;
			case 15:
				mini_unset_built_in(master->envdata, "CHANGE_VALUE"); break;
			case 16:
				mini_unset_built_in(master->envdata, "CHANGE_VALUE"); break;
			case 17:
				mini_unset_built_in(master->envdata, "TES;T"); break;
			case 18:
				mini_unset_built_in(master->envdata, "TES.T"); break;
			case 19:
				mini_unset_built_in(master->envdata, "TES+T"); break;
			case 20:
				mini_unset_built_in(master->envdata, "TES=T"); break;
			case 21:
				mini_unset_built_in(master->envdata, "TES}T"); break;
			case 22:
				mini_unset_built_in(master->envdata, "TES{T"); break;
			case 23:
				mini_unset_built_in(master->envdata, "TES-T"); break;
			case 24:
				mini_unset_built_in(master->envdata, "-TEST"); break;
			case 25:
				mini_unset_built_in(master->envdata, "_TEST"); break;
			case 26:
				mini_unset_built_in(master->envdata, "TES_T"); break;
			case 27:
				mini_unset_built_in(master->envdata, "TEST_"); break;
			case 28:
				mini_unset_built_in(master->envdata, "TE*ST"); break;
			case 29:
				mini_unset_built_in(master->envdata, "TES#T"); break;
			case 30:
				mini_unset_built_in(master->envdata, "TES@T"); break;
			case 31:
				mini_unset_built_in(master->envdata, "TES!T"); break;
			case 32:
				mini_unset_built_in(master->envdata, "============"); break;
			case 33:
				mini_unset_built_in(master->envdata, "+++++++"); break;
			case 34:
				mini_unset_built_in(master->envdata, "________"); break;
			case 35:
				mini_unset_built_in(master->envdata, "export"); break;
			case 36:
				mini_unset_built_in(master->envdata, "echo"); break;
			case 37:
				mini_unset_built_in(master->envdata, "pwd"); break;
			case 38:
				mini_unset_built_in(master->envdata, "cd"); break;
			case 39:
				mini_unset_built_in(master->envdata, "unset"); break;
			case 40:
				mini_unset_built_in(master->envdata, "sudo"); break;
			case 41:
				mini_unset_built_in(master->envdata, "TES^T"); break;
			case 42:
				mini_unset_built_in(master->envdata, "TES!T"); break;
			default:
				dprintf(1, "WTF is happening ?");
		}
		a++;
	}
	dprintf(1, "\n");
	mini_export_built_in(master->envdata, NULL);
	dprintf(1, "\n");
	mini_env_built_in(master->envdata);
}
