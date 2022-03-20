/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:39:18 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/20 15:34:50 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**mini_linked_to_split(t_list *lst, size_t lst_size)
{
	t_env	*link;
	char	**split;
	char	*tmp;
	size_t	a;

	a = 0;
	split = malloc(sizeof(char *) * (lst_size + 1));
	if (!split)
		return (NULL);
	while (a < lst_size && lst)
	{
		link = lst->content;
		split[a] = ft_strjoin(link->name, "=");
		tmp = split[a];
		split[a] = ft_strjoin(split[a], link->value);
		free (tmp);
		lst = lst->next;
		a++;
	}
	split[a] = NULL;
	return (split);
}

int	mini_env_built_in(t_envdata *envdata, int fd_out)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	env_var = NULL;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		if (env_var->value)
			ft_dprintf(fd_out, "%s=%s\n", env_var->name, env_var->value);
		envdata->lst = envdata->lst->next;
	}
	return (0);
}
