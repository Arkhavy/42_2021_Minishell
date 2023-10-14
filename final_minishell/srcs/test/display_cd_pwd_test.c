/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_cd_pwd_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:01:34 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/06 15:18:42 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		mini_pwd_built_in();
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
	mini_pwd_built_in();
	env_var = mini_get_env_var(master->envdata, "PWD");
	if (env_var)
		dprintf(1, "ENV PWD = %s\n", env_var->value);
	env_var = mini_get_env_var(master->envdata, "OLDPWD");
	if (env_var)
		dprintf(1, "ENV OLDPWD = %s\n", env_var->value);
}