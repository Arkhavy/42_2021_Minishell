/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:23:41 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/09 11:06:41 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	display_errors(void)
{
	dprintf(2, "\n\nDISPLAY ERRORS\n\n");
	mini_error_print(E_AC, DFI, DLI, DFU);
	dprintf(2, "\n\n");
	mini_error_print(E_MALLOC, DFI, DLI, DFU);
	dprintf(2, "\n\n");
	mini_error_print(E_ENVDATA, DFI, DLI, DFU);
	dprintf(2, "\n\n");
	mini_error_print(E_ID, DFI, DLI, DFU);
	dprintf(2, "\n\n");
	mini_error_print(E_CWD, DFI, DLI, DFU);
	dprintf(2, "\n\n");
	mini_error_print(E_HOME, DFI, DLI, DFU);
	dprintf(2, "\n\n");
	mini_error_print(E_CHDIR, DFI, DLI, DFU);
	dprintf(2, "\n\n");
	mini_error_print(E_OLDPWD, DFI, DLI, DFU);
	dprintf(2, "\n\n");
	mini_error_print(E_EXIT_NUM, DFI, DLI, DFU);
	dprintf(2, "\n\n");
	mini_error_print(E_EXIT_ARG, DFI, DLI, DFU);
	dprintf(2, "\n\n");
	mini_error_print(E_SUPPORT, DFI, DLI, DFU);
	dprintf(2, "\n\n");
	mini_error_print(E_SYNTAX, DFI, DLI, DFU);
	dprintf(2, "\n\n");
	mini_warning_print(W_PATH, DFI, DLI, DFU);
	dprintf(2, "\n\n");
}
