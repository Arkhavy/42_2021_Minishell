/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:31:45 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/23 13:22:01 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_cmd(char *str, char *dest, t_master *master)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (mini_error(E_MALLOC, NULL, ENOMEM, DFI, DLI, DFU));
	cmd->raw = ft_strdup(str);
	if (dest[0] != '>' && dest[0] != '&' && !base_fd(dest[0]))
		init_cmd_no_redir(dest, master, cmd);
	else
		init_cmd_redir(dest, master, cmd);
	return (0);
}

int	check_nb_dq(char *str)
{
	int	i;
	int	d_q;

	i = 0;
	d_q = 0;
	while (str[i])
	{
		if (str[i] == '"')
			d_q++;
		i++;
	}
	return (d_q);
}

char	*un_double_quote(char *str)
{
	int		i;
	int		a;
	char	*dest;

	i = 0;
	a = 0;
	dest = malloc(sizeof(char) * (ft_strlen(str) - check_nb_dq(str) + 1));
	while (str[i])
	{
		if (str[i] != '"')
		{
			dest[a] = str[i];
			a++;
		}
		i++;
	}
	dest[a] = '\0';
	free(str);
	return (dest);
}


static int	mini_check_spaces_heredoc(char *str, int i)
{
	i += 2;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

static char	*remove_heredoc(char *str)
{
	int		i;
	int		a;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			a = i;
			i += mini_check_spaces_heredoc(str, i);
			tmp1 = ft_substr(str, 0, a);
			tmp2 = ft_substr(str, i, ft_strlen(str));
			free (str);
			str = ft_strfreejoin(tmp1, tmp2);
			i = 0;
		}
		else
			i++;
	}
	return (str);
}

char	*pre_sort(char *str, t_master *master)
{
	int		*tab_index;
	char	*dest;
	int		tmp;

	tab_index = init_tab_index();
	tmp = 0;
	dest = NULL;
	str = remove_heredoc(str);
	while (str[tab_index[0]])
	{
		tmp = tab_index[1];
		tab_index[1] = redir_check(str, dest, tab_index, master);
		if (tab_index[1] == -1)
			break ;
		tab_index[1] = pipe_check(str, dest, tab_index, master);
		tab_index[1] = end_check(str, dest, tab_index, master);
		if (tab_index[1] > tmp)
			tab_index[0] = tab_index[1];
		else
			tab_index[0]++;
	}
	free(tab_index);
	return (str);
}
