/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:58:24 by ljohnson          #+#    #+#             */
/*   Updated: 2022/06/17 09:53:17 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*mini_create_new_line(t_env *env_var, char *line, int i)
{
	char	*new_line;

	new_line = ft_substr(line, 0, i);
	if (!new_line)
		return (NULL);
	new_line = ft_strfreejoin(new_line, ft_strdup(env_var->value));
	if (!new_line)
		return (NULL);
	i += env_var->name_len + 1;
	new_line = ft_strfreejoin(new_line, ft_substr(line, i, ft_strlen(line)));
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*mini_get_varname(char *line, int i)
{
	char	*varname;
	int		a;

	a = i;
	dprintf(STDOUT_FILENO, "line : |%s|\n", line);
	while (line[a] && ft_ischarset(line[a], ENVNAME_CSET))
		a++;
	dprintf(STDOUT_FILENO, "char : |%c|\n", line[a]);
	dprintf(STDOUT_FILENO, "i = %d | a = %d\n", i, a);
	varname = ft_substr(line, i, a - i);
	if (!varname)
		return (NULL);
	dprintf(STDOUT_FILENO, "varname : |%s|\n", varname);
	return (varname);
}

char	*mini_expand_env_var(t_envdata *envdata, char *line, int i)
{
	t_env	*env_var;
	char	*varname;
	char	*new_line;

	if (!line || !line[0] || !line[i] || line[i] != '$')
		return (line);
	if (line[i] == '$' && line[i + 1] == '?')
		new_line = mini_create_new_line(env_var, line, i); //fix
	varname = mini_get_varname(line, i + 1);
	if (!varname)
		return (line);
	env_var = mini_get_env_var(envdata, varname);
	free (varname);
	if (!env_var)
		return (line);
	new_line = mini_create_new_line(env_var, line, i);
	if (!new_line)
		return (line);
	free (line);
	return (new_line);
}
