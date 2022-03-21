/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:21:26 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/21 13:58:27 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_is_arg_valid(char *arg)
{
	size_t	a;
	int		sign;

	a = 0;
	sign = 0;
	if (!arg)
		return (1);
	if (ft_big_atol(arg) > INT_MAX || ft_big_atol(arg) < INT_MIN)
		return (2);
	while (arg[a])
	{
		if (!ft_isdigit(arg[a]))
		{
			if (sign == 0 && (arg[a] == '-' || arg[a] == '+'))
				sign = 1;
			else if (sign == 1 && (arg[a] == '-' || arg[a] == '+'))
				return (2);
			else if (arg[a] == ' ' && arg[a + 1] != '\0')
				return (3);
			else
				return (2);
		}
		a++;
	}
	return (0);
}

int	mini_exit_built_in(t_master *master, char *raw_arg, int fd_out)
{
	size_t	a;
	t_env	*env_var;

	a = 0;
	env_var = mini_get_env_var(master->envdata, "SHLVL");
	if (!env_var)
		env_var = mini_set_env_var(master->envdata, "SHLVL", "1");
	ft_putendl_fd("exit", fd_out);
	if (mini_is_arg_valid(raw_arg) == 1)
		ft_putstr_fd("//set g_errno to 0", -1);
	else if (mini_is_arg_valid(raw_arg) == 2)
	{
		mini_errprint(E_EXT_NUM, DFI, DLI, DFU);
		ft_putstr_fd("//set g_errno to 255", -1);
		mini_set_new_value(master->envdata, "SHLVL", ft_strdup("1"));
	}
	else if (mini_is_arg_valid(raw_arg) == 3)
	{
		mini_errprint(E_EXT_ARG, DFI, DLI, DFU);
		ft_putstr_fd("//set g_errno to 1", -1);
		mini_set_new_value(master->envdata, "SHLVL", ft_strdup("1"));
	}
	mini_end_of_program(master);
	exit(-1);
	return (0);
}
