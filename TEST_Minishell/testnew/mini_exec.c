/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 09:26:45 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/25 09:36:41 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "oskour.h"

char	*mini_get_file(t_envdata envdata, char *cmd)
{
	size_t	a;
	char	*tmp;
	char	*file;

	a = 0;
	file = NULL;
	while (envdata.paths[a])
	{
		tmp = file;
		file = ft_strjoin(envdata.paths[a], cmd);
		free (tmp);
		if (!access (file, F_OK))
			break ;
		a++;
	}
	if (access(file, F_OK) == -1)
	{
		free (file);
		mini_errprint(ERR_CMD, DFI, DLI, DFU);
		return (ft_strdup(cmd));
	}
	return (file);
}

char	*mini_get_cmd(t_envdata envdata, char *rawcmd)
{
	char	*cmd;
	char	*file;

	if (ft_int_strchr(rawcmd, ' ') > -1)
		cmd = ft_substr(rawcmd, 0, ft_int_strchr(rawcmd, ' '));
	else
		cmd = ft_strdup(rawcmd);
	if (!access(cmd, F_OK));
		return (cmd);
	file = mini_get_file(envdata, cmd);
	free (cmd);
	return (file);
}