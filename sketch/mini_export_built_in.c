/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_built_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:55:53 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/05 19:17:32 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

//IT WORKS
//Will be used only if the syntax "export NAME=value" is OK in the parsing
//newvar = "NAME=value"
//ATTENTION = Les doubles quotes doivent être retirées si elles sont présentes
/**
 * #CAS RELOUS :
 * export ARG=value
 * export "ARG"=value
 * export ARG="value"
 * export "ARG"="value"
 * export ""ARG"="value""
 * value = NULL
*/

//Fonctionne, mais besoin d'un parsing solide avant ou pendant la fonction
	//dans le else, on peut check si name et value ont des quotes
	//si c'est le cas, trim pour ne garder que ce qui nous intéresse
	//les quotes autour de l'ensemble de l'arg seront gérées avant la fonction
	//ft_strtrim fera le boulot très efficacement
//Besoin de séparer export en 3/4 fonctions : 
//if !newvar, print envlist

int	mini_check_var_existence(t_envdata *envdata, char *varname)
{
	t_env	*env_var;
	int		cmp_data;
	int		cmp_err;

	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		cmp_data = ft_strncmp(varname, env_var->name, ft_strlen(varname));
		cmp_err = ft_strncmp(varname, env_var->name, ft_strlen(varname));
		if (!cmp_data || cmp_err == 256)
			return (0);
		envdata->lst = envdata->lst->next;
	}
	return (1);
}

void	mini_replace_var(t_envdata *envdata, char *newvar, t_env *env_var)
{
	t_env	*env_var2;
	char	*varname;
	int		index;

	envdata->lst = envdata->start;
	index = ft_int_strchr(newvar, '=');
	varname = env_var->name;
	while (envdata->lst)
	{
		env_var2 = envdata->lst->content;
		if (!ft_strncmp(varname, env_var2->name, ft_strlen(varname)))
		{
			free (env_var2->value);
			env_var2->value = ft_substr(newvar, index + 1, ft_strlen(newvar));
			break ;
		}
		envdata->lst = envdata->lst->next;
	}
	free (varname);
	free (env_var);
}

void	mini_export_display(t_envdata *envdata, int fd_out)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		ft_dprintf(fd_out, "declare -x %s=\"%s\"\n",
			env_var->name, env_var->value);
		envdata->lst = envdata->lst->next;
	}
}

int	mini_export_built_in(t_envdata *envdata, char *newvar, int fd_out)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	if (!newvar || !newvar[0])
		mini_export_display(envdata, fd_out);
	else
	{
		env_var = malloc(sizeof(t_env));
		if (!env_var)
			return (mini_errprint(ERR_MALLOC, DFI, DLI, DFU));
		env_var->name = ft_substr(newvar, 0, ft_int_strchr(newvar, '='));
		if (!mini_check_var_existence(envdata, env_var->name))
			mini_replace_var(envdata, newvar, env_var);
		else
		{
			envdata->lst = envdata->start;
			env_var->value = ft_substr(newvar,
					ft_int_strchr(newvar, '=') + 1, ft_strlen(newvar));
			ft_lstadd_back(&envdata->lst, ft_lstnew(env_var));
			envdata->lst_size++;
		}
	}
	return (0);
}
