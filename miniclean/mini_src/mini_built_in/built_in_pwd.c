/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:34:35 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/20 10:27:04 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_test.h>

int	mini_pwd_built_in(int fd_out)
{
	char	*current_cwd;

	current_cwd = getcwd(NULL, 0);
	if (!current_cwd)
		return (mini_errprint(E_CWD, DFI, DLI, DFU));
	ft_dprintf(fd_out, "%s\n", current_cwd);
	free (current_cwd);
	return (0);
}

// int	mini_pwd_built_in(t_envdata *envdata, int fd_out)
// {
// 	char	*str;
// 	t_env	*env_var;

// 	str = NULL;
// 	envdata->lst = envdata->start;
// 	while (envdata->lst)
// 	{
// 		env_var = envdata->lst->content;
// 		if (!ft_strncmp(env_var->name, "PWD=", 4))
// 		{
// 			ft_dprintf(fd_out, "%s\n", env_var->value);
// 			return (0);
// 		}
// 		envdata->lst = envdata->lst->next;
// 	}
// 	if (!envdata->lst)
// 	{
// 		str = getcwd(NULL, 0);
// 		ft_dprintf(fd_out, "%s\n", str);
// 		free (str);
// 	}
// 	return (0);
// }
