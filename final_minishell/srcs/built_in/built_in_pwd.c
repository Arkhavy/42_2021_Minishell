/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:12:13 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/08 09:38:38 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_pwd_built_in(void)
{
	char	*current_cwd;

	current_cwd = getcwd(NULL, 0);
	if (!current_cwd)
		return (mini_error(EINVAL));
	ft_dprintf(1, "%s\n", current_cwd);
	free (current_cwd);
	return (0);
}