/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_display2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:31:17 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/08 14:22:04 by ljohnson         ###   ########lyon.fr   */
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

static void	init_unset_test(t_master *master)
{
	mini_export_built_in(master->envdata, "NOVALUE1", 1);
	mini_export_built_in(master->envdata, "NOVALUE2", 1);
	mini_export_built_in(master->envdata, "NOVALUE3", 1);

	mini_export_built_in(master->envdata, "VALUE1=value", 1);
	mini_export_built_in(master->envdata, "VALUE2=value2", 1);
	mini_export_built_in(master->envdata, "VALUE3=value3", 1);

	mini_export_built_in(master->envdata, "VOIDVALUE1=", 1);
	mini_export_built_in(master->envdata, "VOIDVALUE2=", 1);
	mini_export_built_in(master->envdata, "VOIDVALUE3=", 1);

	mini_export_built_in(master->envdata, "APPEND1=one", 1);
	mini_export_built_in(master->envdata, "APPEND1+= two", 1);
	mini_export_built_in(master->envdata, "APPEND1+= three", 1);

	mini_export_built_in(master->envdata, "APPEND2+=one", 1);
	mini_export_built_in(master->envdata, "APPEND2+= two", 1);
	mini_export_built_in(master->envdata, "APPEND2+= three", 1);

	mini_export_built_in(master->envdata, "CHANGE_VALUE=one", 1);
	mini_export_built_in(master->envdata, "CHANGE_VALUE=two", 1);
	mini_export_built_in(master->envdata, "CHANGE_VALUE=three", 1);
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
		mini_export_built_in(master->envdata, NULL, 1);
		dprintf(1, "\n");
		mini_env_built_in(master->envdata, 1);
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
	mini_export_built_in(master->envdata, NULL, 1);
	dprintf(1, "\n");
	mini_env_built_in(master->envdata, 1);
}

void	display_cd_pwd_test(t_master *master)
{
	size_t	a;
	size_t	cases;
	t_env	*env_var;

	dprintf(1, "\n\nDISPLAY CD PWD BUILT IN\n\n");
	a = 0;
	cases = 24;
	while (a <= cases)
	{
		dprintf(1, "\n");
		dprintf(1, "\nPWD BUILT IN\n");
		mini_pwd_built_in(1);
		env_var = mini_get_env_var(master->envdata, "PWD");
		if (env_var)
			dprintf(1, "ENV PWD = %s\n", env_var->value);
		env_var = mini_get_env_var(master->envdata, "OLDPWD");
		if (env_var)
			dprintf(1, "ENV OLDPWD = %s\n", env_var->value);
		dprintf(1, "\n\nCASE %zu/%zu\n\n", a, cases);
		switch (a)
		{
			case 0:
				mini_cd_built_in(master->envdata, ".."); break ;
			case 1:
				mini_cd_built_in(master->envdata, "~"); break ;
			case 2:
				mini_cd_built_in(master->envdata, ""); break ;
			case 3:
				mini_cd_built_in(master->envdata, "~/Cursus"); break ;
			case 4:
				mini_cd_built_in(master->envdata, "private_minishell"); break ;
			case 5:
				mini_cd_built_in(master->envdata, "minishell_v2"); break ;
			case 6:
				mini_cd_built_in(master->envdata, "../notes"); break;
			case 7:
				mini_cd_built_in(master->envdata, "../obelair"); break;
			case 8:
				mini_cd_built_in(master->envdata, "../.."); break;
			case 9:
				mini_cd_built_in(master->envdata, "ouaf"); break;
			case 10:
				mini_cd_built_in(master->envdata, "ouef"); break;
			case 11:
				mini_cd_built_in(master->envdata, "notes"); break;
			case 12:
				mini_cd_built_in(master->envdata, NULL); break;
			case 13:
				mini_cd_built_in(master->envdata, "-"); break;
			case 14:
				mini_cd_built_in(master->envdata, ".."); break;
			case 15:
				mini_cd_built_in(master->envdata, "/Cursus/private_minishell/minishell_v2/ouaf"); break;
			case 16:
				mini_cd_built_in(master->envdata, "/Cursus/private_minishell/minishell_v2/srcs/built_in"); break;
			case 17:
				mini_cd_built_in(master->envdata, "--"); break;
			case 18:
				mini_cd_built_in(master->envdata, "-"); break;
			case 19:
				mini_cd_built_in(master->envdata, "../../.."); break;
			case 20:
				mini_cd_built_in(master->envdata, "."); break;
			case 21:
				mini_cd_built_in(master->envdata, "/Users"); break;
			case 22:
				mini_cd_built_in(master->envdata, NULL); break;
			case 23:
				mini_cd_built_in(master->envdata, "Cursus/private_minishell/minishell_v2/srcs/managers"); break;
			case 24:
				mini_cd_built_in(master->envdata, "/Users"); break;
		}
		a++;
	}
	dprintf(1, "\n");
	dprintf(1, "\nPWD BUILT IN\n");
	mini_pwd_built_in(1);
	env_var = mini_get_env_var(master->envdata, "PWD");
	if (env_var)
		dprintf(1, "ENV PWD = %s\n", env_var->value);
	env_var = mini_get_env_var(master->envdata, "OLDPWD");
	if (env_var)
		dprintf(1, "ENV OLDPWD = %s\n", env_var->value);
}


//WiP export + echo
//Exit will be tested with readline, still need to make tests for it
//Indexing of env_vars in progress
//export display in progress, need indexing

//Parsing will need rework and more thoughts
//IT'S SLOWLY BUILDING WOAH
//Might need fractionned schedules to work more ?