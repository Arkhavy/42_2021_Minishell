/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:34:35 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/20 14:22:45 by ljohnson         ###   ########lyon.fr   */
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
