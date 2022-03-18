/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:47:13 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/18 17:52:26 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_test.h>

//Display all vars if there is no args
int	mini_export_display(t_envdata *envdata, int fd_out)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		ft_dprintf(fd_out, "declare -x ");
		if (!env_var->value)
			ft_dprintf(fd_out, "%s\n", env_var->name);
		else
			ft_dprintf(fd_out, "%s=\"%s\"\n", env_var->name, env_var->value);
		envdata->lst = envdata->lst->next;
	}
	return (0);
}

//Add or append a var or replace it depending on the index of = and +=
void	mini_add_var(t_envdata *envdata, char *raw_arg, int append)
{
	t_env	*env_var;
	char	*var_name;
	char	*var_value;

	if (append == 1)
		var_name = ft_substr(raw_arg, 0, ft_int_strchr(raw_arg, '+'));
	else
		var_name = ft_substr(raw_arg, 0, ft_int_strchr(raw_arg, '='));
	var_value = ft_substr(raw_arg, ft_int_strchr(raw_arg, '=') + 1,
			ft_strlen(raw_arg));
	env_var = mini_get_env_var(envdata, var_name);
	if (!env_var)
		env_var = mini_set_env_var(envdata, var_name, var_value);
	else
	{
		free(var_name);
		if (append == 1)
			env_var->value = ft_strfreejoin(env_var->value, var_value);
		else
		{
			free (env_var->value);
			env_var->value = var_value;
		}
	}
}

//Check any character that should not belong to a varname
int	mini_check_raw_arg(char *raw_arg)
{
	size_t	a;

	a = 0;
	if (raw_arg[0] < 'A' || (raw_arg[0] > 'Z' && raw_arg[0] < 'a')
		|| raw_arg[0] > 'z')
		return (-1);
	while (raw_arg[a])
	{
		if (raw_arg[a] < '0' || (raw_arg[a] > '9' && raw_arg[a] < 'A')
			|| (raw_arg[a] > 'Z' && raw_arg[a] < 'a') || raw_arg[a] > 'z')
		{
			if (((raw_arg[a] == '+' && raw_arg[a + 1] == '=')
					|| raw_arg[a] == '=') && a != 0)
				return (a);
			return (-1);
		}
		a++;
	}
	return (a);
}

//Will need to remove quotes before going in this function
int	mini_export_built_in(t_envdata *envdata, char *raw_arg, int fd_out)
{
	t_env	*env_var;
	int		sep_index;

	if (!raw_arg || !raw_arg[0])
		return (mini_export_display(envdata, fd_out));
	sep_index = mini_check_raw_arg(raw_arg);
	dprintf(2, "sep_index %d | %s\n", sep_index, raw_arg);
	env_var = NULL;
	if (sep_index == -1)
		return (mini_errprint(E_ID, DFI, DLI, DFU));
	else if (sep_index == (int)ft_strlen(raw_arg))
	{
		env_var = mini_get_env_var(envdata, raw_arg);
		if (!env_var)
			env_var = mini_set_env_var(envdata, raw_arg, NULL);
	}
	else
	{
		if (raw_arg[sep_index] == '+')
			mini_add_var(envdata, raw_arg, 1);
		else
			mini_add_var(envdata, raw_arg, 0);
	}
	return (0);
}
