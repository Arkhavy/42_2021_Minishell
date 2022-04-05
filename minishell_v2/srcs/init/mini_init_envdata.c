/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init_envdata.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:22:45 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/05 08:01:43 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_init_paths(t_envdata *envdata)
{
	t_env	*env_var;
	char	*tmp;
	size_t	a;

	a = 0;
	tmp = NULL;
	env_var = mini_get_env_var(envdata, "PATH");
	if (!env_var || !env_var->value)
		return (mini_warning_print(W_PATH, DFI, DLI, DFU));
	envdata->paths = ft_split(env_var->value, ':');
	if (!envdata->paths)
		return (mini_error_print(E_MALLOC, DFI, DLI, DFU));
	while (envdata->paths[a])
	{
		tmp = envdata->paths[a];
		envdata->paths[a] = ft_strjoin(envdata->paths[a], "/");
		free (tmp);
		a++;
	}
	return (0);
}

int	mini_init_env_var(t_envdata *envdata, char *env)
{
	t_env	*env_var;
	int		sep_index;
	int		len;

	if (!env)
		return (1);
	sep_index = ft_int_strchr(env, '=');
	len = ft_strlen(env);
	env_var = ft_calloc(1, sizeof(t_env));
	if (!env_var)
		return (mini_error_print(E_MALLOC, DFI, DLI, DFU));
	if (sep_index > -1)
	{
		env_var->name = ft_substr(env, 0, sep_index);
		env_var->value = ft_substr(env, sep_index + 1, len);
	}
	else
	{
		env_var->name = ft_strdup(env);
		env_var->value = NULL;
	}
	env_var->name_len = ft_strlen(env_var->name);
	env_var->index = -1;
	ft_lstadd_back(&envdata->lst, ft_lstnew(env_var));
	return (0);
}

int	mini_init_envdata(t_envdata *envdata, char **env)
{
	size_t	a;

	a = 0;
	envdata->lst = NULL;
	envdata->lst_size = 0;
	envdata->paths = NULL;
	if (!env || !env[a])
		return (0);
	while (env[a])
	{
		if (mini_init_env_var(envdata, env[a]))
			return (1);
		envdata->lst_size++;
		a++;
	}
	envdata->start = envdata->lst;
	if (mini_init_paths(envdata))
		return (1);
	return (0);
}
