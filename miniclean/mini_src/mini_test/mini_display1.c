/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_display1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:20:21 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/29 14:05:57 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minitest.h>

void	display_errors(void)
{
	dprintf(2, "\n\nDISPLAY ERROR MESSAGES\n\n");
	mini_errprint(E_AC, DFI, DLI, DFU);
	mini_errprint(E_INIT, DFI, DLI, DFU);
	mini_errprint(E_MALLOC, DFI, DLI, DFU);
	mini_errprint(E_PIPE, DFI, DLI, DFU);
	mini_errprint(E_FORK, DFI, DLI, DFU);
	mini_errprint(E_DUP, DFI, DLI, DFU);
	mini_errprint(E_ACCESS_F, DFI, DLI, DFU);
	mini_errprint(E_ACCESS_R, DFI, DLI, DFU);
	mini_errprint(E_ACCESS_W, DFI, DLI, DFU);
	mini_errprint(E_ACCESS_X, DFI, DLI, DFU);
	mini_errprint(E_EXECVE, DFI, DLI, DFU);
	mini_errprint(E_OPEN, DFI, DLI, DFU);
	mini_errprint(E_READ, DFI, DLI, DFU);
	mini_errprint(E_WRITE, DFI, DLI, DFU);
	mini_errprint(E_CLOSE, DFI, DLI, DFU);
	mini_errprint(E_HOME, DFI, DLI, DFU);
	mini_errprint(E_OLDPWD, DFI, DLI, DFU);
	mini_errprint(E_CHDIR, DFI, DLI, DFU);
	mini_errprint(E_PARSE, DFI, DLI, DFU);
	mini_errprint(E_ID, DFI, DLI, DFU);
	mini_errprint(E_CWD, DFI, DLI, DFU);
	mini_errprint(E_EXT_NUM, DFI, DLI, DFU);
	mini_errprint(E_EXT_ARG, DFI, DLI, DFU);
	mini_errprint(E_PATH, DFI, DLI, DFU);
	mini_errprint(E_HANDLER, DFI, DLI, DFU);
	mini_errprint(E_EMPTY, DFI, DLI, DFU);
	mini_errprint(E_CONTENT, DFI, DLI, DFU);
	mini_errprint(E_QUOTE, DFI, DLI, DFU);
	mini_errprint(E_PARSING, DFI, DLI, DFU);
}

void	display_env_main(char **env)
{
	size_t	a;

	a = 0;
	dprintf(1, "\n\nDISPLAY ENV MAIN\n\n");
	while (env[a])
	{
		dprintf(1, "%s\n", env[a]);
		a++;
	}
}

void	display_env_minishell(t_master *master)
{
	t_env	*env_var;
	size_t	a;

	master->envdata->lst = master->envdata->start;
	env_var = NULL;
	a = 0;
	dprintf(1, "\n\nDISPLAY ENV MINISHELL\n\n");
	while (master->envdata->lst)
	{
		env_var = master->envdata->lst->content;
		dprintf(1, "%zu:	%s=%s\n", a, env_var->name, env_var->value);
		master->envdata->lst = master->envdata->lst->next;
		a++;
	}
}

void	display_envsplit_minishell(t_master *master)
{
	size_t	a;
	char	**envsplit;

	a = 0;
	master->envdata->lst = master->envdata->start;
	envsplit = mini_linked_to_split(master->envdata->lst,
			master->envdata->lst_size);
	dprintf(1, "\n\nDISPLAY ENVSPLIT MINISHELL\n\n");
	while (envsplit[a])
	{
		dprintf(1, "%zu:	%s\n", a, envsplit[a]);
		a++;
	}
	ft_free_split(envsplit);
}

void	display_env_paths(t_master *master)
{
	size_t	a;

	a = 0;
	dprintf(1, "\n\nDISPLAY ENVDATA PATHS\n\n");
	while (master->envdata->paths[a])
	{
		dprintf(1, "%zu:	%s\n", a, master->envdata->paths[a]);
		a++;
	}
}
