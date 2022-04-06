/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_workers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:51:49 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/29 18:12:53 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_is_builtin(char *raw_cmd)
{
	if (!ft_strncmp(raw_cmd, "echo", ft_strlen("echo")))
		return (1);
	else if (!ft_strncmp(raw_cmd, "cd", ft_strlen("cd")))
		return (2);
	else if (!ft_strncmp(raw_cmd, "env", ft_strlen("env")))
		return (3);
	else if (!ft_strncmp(raw_cmd, "exit", ft_strlen("exit")))
		return (4);
	else if (!ft_strncmp(raw_cmd, "export", ft_strlen("export")))
		return (5);
	else if (!ft_strncmp(raw_cmd, "pwd", ft_strlen("pwd")))
		return (6);
	else if (!ft_strncmp(raw_cmd, "unset", ft_strlen("unset")))
		return (7);
	return (0);
}
