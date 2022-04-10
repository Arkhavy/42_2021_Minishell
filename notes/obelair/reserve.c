/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 07:57:54 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/26 10:47:58 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

READLINE
//Loop servant à récupérer les données envoyé dans minishell via readline
// int	loop_readline(t_master *master)
// {
// 	while (1)
// 	{
// 		if (g_error)
// 			master->line = readline(PROMPT_ERR);
// 		else
// 			master->line = readline(PROMPT);
// 		parsing(master);
// 	}
// 	ft_free_split(master->envdata->paths);
// 	mini_free_envlist(master->envdata);
// 	free (master->fdstruct->startpath);
// 	return (0);
// }


INIT TOKEN
//Compte le nombre de pipe de la commande reçue
// static size_t	nb_pipe(char *line)
// {
// 	size_t	nb_pipe;
// 	char	quote;

// 	nb_pipe = 0;
// 	quote = 0;
// 	while (*line)
// 	{
// 		if ((*line == '"' || *line == '\'') && !quote)
// 			quote = *line;
// 		else if (quote == *line)
// 			quote = 0;
// 		if (*line == '|' && !quote)
// 			nb_pipe++;
// 		line++;
// 	}
// 	return (nb_pipe);
// }

// //Initialise tous les tokens en fonction du nombre de pipe présent
// 	//dans la line de commande récupérée
// int	mini_init_token(t_master *master)
// {
// 	size_t	i;

// 	master->nb_tok = nb_pipe(master->line);
// 	master->token = ft_calloc(master->nb_tok, sizeof(t_token));
// 	if (!master->token)
// 		return (mini_errprint(E_MALLOC, DFI, DLI, DFU));
// 	i = -1;
// 	while (++i < master->nb_tok)
// 	{
// 		master->token[i].cmd = NO_CMD;
// 		master->token[i].fd_in = 0;
// 		master->token[i].fd_out = 1;
// 		master->token[i].arg = NULL;
// 		master->token[i].path = NULL;
// 	}
// 	return (0);
// }

.H
// int		loop_readline(t_master *master);
//size_t	nb_pipe(char *line);
// int		mini_init_token(t_master *master);

// /*-------------------- parsing_checker_line.c --------------------*/

// void	skip_space(char **line);
// int		check_succesive_ope(char **line);
// int		loop_line(char *line, char *quote, char *last);
// int		check_line(char *line);

// /*-------------------- mini_parsing.c --------------------*/

// char	*get_args(char *line);
// int		get_command(char **line, size_t i);
// int		fill_token(t_master *master);
// int		parsing(t_master *master);

// struct s_token
// {
// 	t_cmd	cmd;
// 	int		fd_in;
// 	int		fd_out;
// 	char	*arg;
// 	char	*path;
// };

// enum e_cmd
// {
// 	NO_CMD,
// 	C_ECHO,
// 	C_CD,
// 	C_PWD,
// 	C_EXPORT,
// 	C_UNSET,
// 	C_ENV,
// 	C_EXIT,
// };

	// t_token		*token;
// typedef struct s_token		t_token;
// typedef enum e_cmd			t_cmd;