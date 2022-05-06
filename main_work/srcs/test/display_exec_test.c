/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_exec_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:50:52 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/06 07:45:05 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
struct s_execdata
{
	t_list	*lst;
	size_t	lst_size;
	void	*start;
};

//link of execdata->lst
struct s_cmd
{
	int		token_id;
	char	*raw;
	char	**split;
};
1 = execve
2 = built-in (return atm)
3 = redirection

./minishell "cat -e Makefile" "wc -l" > outfile.txt 
cat -e Makefile | wc -l > outfile2.txt

./minishell "ls -l" "wc -l" > outfile.txt
ls - l | wc -l >> outfile.txt

./minishell "cat -e Makefile" "cat -e" "cat -e" "cat -e"\
"cat -e" "cat -e" "cat -e" "cat -e" "cat -e" "cat -e" > outfile.txt
cat -e Makefile | cat -e | cat -e | cat -e | cat -e | cat -e \
| cat -e | cat -e | cat -e | cat -e > outfile2.txt

time ./minishell "sleep 2" "sleep 2" "sleep 2"

time ./minishell "sleep 2" "sleep 4" "sleep 6" "sleep 2" "sleep 4" \
"sleep 6" "sleep 8" "sleep 2" "sleep 10" "sleep 2"
*/

static void	init_execdata_test(t_execdata *execdata, int ac, char **av)
{
	int		a;
	t_cmd	*cmd;

	a = 1;
	execdata->lst = NULL;
	execdata->lst_size = 0;
	while (a < ac)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
			return ;
		cmd->token_id = IDT_CMD;
		cmd->raw = av[a];
		cmd->split = ft_split(av[a], ' ');
		ft_lstadd_back(&execdata->lst, ft_lstnew(cmd));
		execdata->lst_size++;
		a++;
	}
	execdata->start = execdata->lst;
}

static void	display_execdata_lst(t_execdata *execdata, t_fdstruct *fdstruct)
{
	t_cmd	*cmd;
	int		a;

	execdata->lst = execdata->start;
	while (execdata->lst)
	{
		a = 0;
		cmd = execdata->lst->content;
		while (cmd->split[a])
		{
			dprintf(fdstruct->fd_out, "[%d]: %s ", a, cmd->split[a]);
			a++;
		}
		dprintf(fdstruct->fd_out, "\n");
		execdata->lst = execdata->lst->next;
	}
}

void	display_exec_test(t_master *master, int ac, char **av)
{
	int	fd_link;

	dprintf(1, "before init\n");
	init_execdata_test(master->execdata, ac, av);
	display_execdata_lst(master->execdata, master->fdstruct);
	dprintf(1, "after init, before exec\n");
	fd_link = dup(STDIN_FILENO);
	if (fd_link < 0)
		return ;
	mini_exec_loop(master, fd_link);
	dprintf(1, "after exec, before reset\n");
	// mini_reset_fdstruct(master->fdstruct);
	dprintf(1, "after reset\n");
}
