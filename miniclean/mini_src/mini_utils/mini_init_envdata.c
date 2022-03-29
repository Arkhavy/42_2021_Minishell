/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init_envdata.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:41:15 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/29 20:34:53 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_init_paths(t_envdata *envdata)
{
	char	*tmp;
	t_env	*env_var;
	size_t	a;

	env_var = mini_get_env_var(envdata, "PATH");
	a = 0;
	if (!env_var || !env_var->value)
		return (mini_errprint(E_PATH, DFI, DLI, DFU));
	envdata->paths = ft_split(env_var->value, ':');
	if (!envdata->paths)
		return (mini_errprint(E_MALLOC, DFI, DLI, DFU));
	while (envdata->paths[a])
	{
		tmp = envdata->paths[a];
		envdata->paths[a] = ft_strjoin(envdata->paths[a], "/");
		free (tmp);
		a++;
	}
	return (0);
}

void	*mini_get_env_var_by_index(t_envdata *envdata, int index)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		if (env_var->index == index)
			return (env_var);
		envdata->lst = envdata->lst->next;
	}
	return (NULL);
}

int	mini_index_envdata_lst(t_envdata *envdata, size_t count)
{
	t_env	*v;
	t_env	*c;
	size_t	vlen;
	size_t	clen;

	while (count < envdata->lst_size)
	{
		v = mini_get_env_var_by_index(envdata, -1);
		if (!v)
			return (mini_errprint(E_INDEX, DFI, DLI, DFU));
		v->index = 0;
		vlen = ft_strlen(v->name);
		envdata->lst = envdata->start;
		while (envdata->lst)
		{
			c = envdata->lst->content;
			clen = ft_strlen(c->name);
			if (ft_strncmp(v->name, c->name, ft_get_highest(vlen, clen)) > 0)
				v->index++;
			envdata->lst = envdata->lst->next;
		}
		count++;
	}
	return (0);
}

int	mini_init_env_var(t_envdata *envdata, char *env)
{
	t_env	*env_var;
	int		sep_index;
	int		len;

	sep_index = ft_int_strchr(env, '=');
	len = ft_strlen(env);
	env_var = malloc(sizeof(t_env));
	if (!env_var)
		return (mini_errprint(E_MALLOC, DFI, DLI, DFU));
	env_var->name = ft_substr(env, 0, sep_index);
	env_var->value = ft_substr(env, sep_index + 1, len);
	env_var->index = -1;
	ft_lstadd_back(&envdata->lst, ft_lstnew(env_var));
	envdata->lst_size++;
	return (0);
}

int	mini_init_envdata(t_envdata *envdata, char **env)
{
	size_t	a;

	a = 0;
	envdata->lst = NULL;
	envdata->lst_size = 0;
	envdata->envmain = env;
	envdata->paths = NULL;
	while (env[a])
	{
		if (mini_init_env_var(envdata, env[a]))
			return (1);
		a++;
	}
	envdata->start = envdata->lst;
	if (mini_index_envdata_lst(envdata, 0) || mini_init_paths(envdata))
		return (1);
	return (0);
}
