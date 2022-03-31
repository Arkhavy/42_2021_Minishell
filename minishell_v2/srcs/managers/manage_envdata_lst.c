/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envdata_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:47:37 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/31 13:55:28 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**mini_convert_lst_to_split(t_envdata *envdata)
{
	t_env	*env_var;
	char	**split;
	size_t	a;

	a = 0;
	envdata->lst = envdata->start;
	split = ft_calloc(envdata->lst_size + 1, sizeof(char *));
	if (!split)
		return (NULL);
	while (a < envdata->lst_size && envdata->lst)
	{
		env_var = envdata->lst->content;
		split[a] = ft_strdup(env_var->name);
		if (env_var->value)
		{
			split[a] = ft_strfreejoin(split[a], ft_strdup("="));
			split[a] = ft_strfreejoin(split[a], ft_strdup(env_var->value));
		}
		envdata->lst = envdata->lst->next;
		a++;
	}
	split[a] = NULL;
	return (split);
}
