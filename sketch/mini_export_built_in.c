/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_built_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:55:53 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/09 10:36:00 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

//export
	//ajout potentiel d'une variable dans la linked list env
	//où dans cette liste ? fin ? début ? milieu ??

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
 * if newvar doesn't respect "NAME=value" syntax, don't do anything
 * if +=, we need to append to the ned of value if NAME is found
 * trim_quote servira à régler ces soucis (parsing)
*/

//Fonctionne, mais besoin d'un parsing solide avant ou pendant la fonction
	//les quotes autour de l'ensemble de l'arg seront gérées avant la fonction
	//les quotes autour de name et value seront gérées pendant leur ajout
		//après leur substr
		//avant le checkname
		//avant leur ajout dans la linked lst
	//ft_strtrim fera le boulot très efficacement

int	mini_check_var_name(t_envdata *envdata, char *varname)
{
	t_env	*env_var;
	int		cmp;

	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		cmp = ft_strncmp(varname, env_var->name, ft_strlen(varname));
		if (!cmp || cmp == 256)
			return (0);
		envdata->lst = envdata->lst->next;
	}
	return (1);
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

void	mini_replace_var(t_envdata *envdata, char *newvar, t_env *env_var)
{
	t_env	*env_tmp;
	int		i;

	envdata->lst = envdata->start;
	i = ft_int_strchr(newvar, '=');
	while (envdata->lst)
	{
		env_tmp = envdata->lst->content;
		if (!ft_strncmp(env_var->name, env_tmp->name, ft_strlen(env_var->name)))
		{
			if (newvar[i - 1] == '+')
				env_tmp->value = ft_strfreejoin(env_tmp->value,
						ft_substr(newvar, i + 1, ft_strlen(newvar)));
			else
			{
				free (env_tmp->value);
				env_tmp->value = ft_substr(newvar, i + 1, ft_strlen(newvar));
			}
			break ;
		}
		envdata->lst = envdata->lst->next;
	}
	free (env_var->name);
	free (env_var);
}

void	mini_add_var(t_envdata *envdata, char *newvar, t_env *env_var)
{
	int		i;
	int		len;
	void	*env_var_ptr;

	i = ft_int_strchr(newvar, '=') + 1;
	len = ft_strlen(newvar);
	envdata->lst = envdata->start;
	env_var->value = ft_substr(newvar, i, len);
	env_var_ptr = ft_lstnew(env_var);
	ft_lstadd_back(&envdata->lst, env_var_ptr);
	envdata->lst_size++;
}

int	mini_export_built_in(t_envdata *envdata, char *newvar, int fd_out)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	if (!newvar || !newvar[0])
		mini_export_display(envdata, fd_out);
	else if (ft_int_strchr(newvar, '=') == -1)
		return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
	else
	{
		env_var = malloc(sizeof(t_env));
		if (!env_var)
			return (mini_errprint(ERR_MALLOC, DFI, DLI, DFU));
		if (newvar[ft_int_strchr(newvar, '=') - 1] == '+')
			env_var->name = ft_substr(newvar, 0,
					ft_int_strchr(newvar, '=') - 1);
		else
			env_var->name = ft_substr(newvar, 0, ft_int_strchr(newvar, '='));
		if (!mini_check_var_name(envdata, env_var->name))
			mini_replace_var(envdata, newvar, env_var);
		else
			mini_add_var(envdata, newvar, env_var);
	}
	return (0);
}
