/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd_built_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 09:23:26 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/11 10:18:26 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

//Should be working
//Still thinking about weird cases
int	mini_pwd_built_in(t_envdata *envdata, int fd_out)
{
	char	*str;
	t_env	*env_var;

	str = NULL;
	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		if (!ft_strncmp(env_var->name, "PWD=", 4))
		{
			ft_dprintf(fd_out, "%s\n", env_var->value);
			return (0);
		}
		envdata->lst = envdata->lst->next;
	}
	if (!envdata->lst)
	{
		str = getcwd(NULL, 0);
		ft_dprintf(fd_out, "%s\n", str);
		free (str);
	}
	return (0);
}
