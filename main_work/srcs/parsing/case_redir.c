/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 08:10:46 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/20 09:42:02 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**redir_alone(char *str, t_cmd *cmd)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	cmd->split = malloc(sizeof(char *) * 3);
	cmd->split[2] = NULL;
	cmd->split[0] = ft_strdup(">");
	while (str[i] && str[i - 1] != '>')
		i++;
	while (str[i] && str[i] != ' ')
	{
		a++;
		i++;
	}
	cmd->split[1] = malloc(sizeof(char) * (a + 1));
	i = i - a;
	a = 0;
	while (str[i] && str[i] != ' ')
	{
		cmd->split[1][a] = str[i];
		a++;
		i++;
	}
	cmd->split[1][a] = '\0';
	return (cmd->split);
}

char	**redir_double(char *str, t_cmd *cmd)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	cmd->split = malloc(sizeof(char *) * 3);
	cmd->split[2] = NULL;
	cmd->split[0] = ft_strdup(">>");
	while (str[i] && str[i - 2] != '>')
		i++;
	while (str[i] && str[i] != ' ')
	{
		a++;
		i++;
	}
	cmd->split[1] = malloc(sizeof(char) * (a + 1));
	i = i - a;
	a = 0;
	while (str[i] && str[i] != ' ')
	{
		cmd->split[1][a] = str[i];
		a++;
		i++;
	}
	cmd->split[1][a] = '\0';
	return (cmd->split);
}

char	**redir_ampersand(char *str, t_cmd *cmd)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	cmd->split = malloc(sizeof(char *) * 3);
	cmd->split[2] = NULL;
	cmd->split[0] = ft_strdup(">&");
	while (str[i] && str[i - 1] != '&')
		i++;
	while (str[i] && str[i] != ' ')
	{
		a++;
		i++;
	}
	cmd->split[1] = malloc(sizeof(char) * (a + 1));
	i = i - a;
	a = 0;
	while (str[i] && str[i] != ' ')
	{
		cmd->split[1][a] = str[i];
		a++;
		i++;
	}
	cmd->split[1][a] = '\0';
	return (cmd->split);
}

char	**redir_fd(char *str, t_cmd *cmd)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	cmd->split = malloc(sizeof(char *) * 4);
	cmd->split[3] = NULL;
	cmd->split[1] = ft_strdup(">");
	while (str[i] && str[i + 1] != '>')
		i++;
	while (str[i] && str[i] == ' ')
		i--;
	while (str[i] && base_fd(str[i]))
		i--;
		i++;
	while (str[i] && base_fd(str[i]))
	{
		a++;
		i++;
	}
	cmd->split[0] = malloc(sizeof(char) * (a + 1));
	i = i - a;
	a = 0;
	while (str[i] && base_fd(str[i]))
	{
		cmd->split[0][a] = str[i];
		a++;
		i++;
	}
	cmd->split[0][a] = '\0';
	a = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '>'))
		i++;
	while (str[i] && str[i] != ' ')
	{
		a++;
		i++;
	}
	cmd->split[2] = malloc(sizeof(char) * (a + 1));
	i = i - a;
	a = 0;
	while (str[i] && str[i] != ' ')
	{
		cmd->split[2][a] = str[i];
		a++;
		i++;
	}
	cmd->split[2][a] = '\0';
	return (cmd->split);
}

char	**redir_double_fd(char *str, t_cmd *cmd)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	cmd->split = malloc(sizeof(char *) * 4);
	cmd->split[3] = NULL;
	cmd->split[1] = ft_strdup(">>");
	while (str[i] && str[i + 1] != '>' && str[i + 2] != '>')
		i++;
	while (str[i] && str[i] == ' ')
		i--;
	while (str[i] && base_fd(str[i]))
		i--;
		i++;
	while (str[i] && base_fd(str[i]))
	{
		a++;
		i++;
	}
	cmd->split[0] = malloc(sizeof(char) * (a + 1));
	i = i - a;
	a = 0;
	while (str[i] && base_fd(str[i]))
	{
		cmd->split[0][a] = str[i];
		a++;
		i++;
	}
	cmd->split[0][a] = '\0';
	a = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '>'))
		i++;
	while (str[i] && str[i] != ' ')
	{
		a++;
		i++;
	}
	cmd->split[2] = malloc(sizeof(char) * (a + 1));
	i = i - a;
	a = 0;
	while (str[i] && str[i] != ' ')
	{
		cmd->split[2][a] = str[i];
		a++;
		i++;
	}
	cmd->split[2][a] = '\0';
	return (cmd->split);
}

char	**redir_fd_ampersand(char *str, t_cmd *cmd)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	cmd->split = malloc(sizeof(char *) * 4);
	cmd->split[3] = NULL;
	cmd->split[1] = ft_strdup(">");
	while (str[i] && str[i + 1] != '>' && str[i + 2] != '&')
		i++;
	while (str[i] && str[i] == ' ')
		i--;
	while (str[i] && base_fd(str[i]))
		i--;
		i++;
	while (str[i] && base_fd(str[i]))
	{
		a++;
		i++;
	}
	cmd->split[0] = malloc(sizeof(char) * (a + 1));
	i = i - a;
	a = 0;
	while (str[i] && base_fd(str[i]))
	{
		cmd->split[0][a] = str[i];
		a++;
		i++;
	}
	cmd->split[0][a] = '\0';
	a = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '>' || str[i] == '&'))
		i++;
	while (str[i] && str[i] != ' ')
	{
		a++;
		i++;
	}
	cmd->split[2] = malloc(sizeof(char) * (a + 1));
	i = i - a;
	a = 0;
	while (str[i] && str[i] != ' ')
	{
		cmd->split[2][a] = str[i];
		a++;
		i++;
	}
	cmd->split[2][a] = '\0';
	return (cmd->split);
}
