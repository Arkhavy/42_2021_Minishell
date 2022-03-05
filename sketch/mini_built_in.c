/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 09:52:51 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/05 10:52:19 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

//echo
	//option n
	//affiche logiquement l'argument donné derrière
	//fonctionne avec les pipes ?
	//fonctionne avec les redirections ?
//pwd
	//affichage path working directory
		//variable env pwd ?
		//commande getcwd ?
			//laquelle est la plus intéressante ?
//cd
	//might need pwd
	//change la variable env pwd ?
	//change une variable propre au programme ?
//export
	//ajout potentiel d'une variable dans la linked list env
	//où dans cette liste ? fin ? début ? milieu ??
//unset
	//retrait potentiel d'une variable dans la linked list env ?
	//n'importe quelle variable ?
	//peut potentiellement casser l'exécution
//env
	//probably just printing env var from main
	//each line will be stored separately
		//split or linked list ?
			//split might be annoying to modify afterward
			//linked list might be a solution if we add temp env vars
//exit
	//que doit-on faire exactement ?
	//full return ?
	//full exit ?
	//fin de minishell ?
	//fin du heredoc seulement si on est dedans ?

/*
unlink after open to avoid fd leaks
unlink permet de "free" un fd une fois que celui-ci est close
par toute les sources qui l'utilisent
 */

//Should remove an entire link of the linked list ?
//Or does it only clean the link without removing it ?
//Will be used only if the syntax "unset name" is OK in the parsing
int	mini_bi_unset(t_envdata *envdata, char *varname)
{
	size_t	a;
	t_env	*env_var;
	size_t	len;

	envdata->lst = envdata->start;
	a = 0;
	len = ft_strlen(varname);
	env_var = envdata->lst->content;
	while (ft_strncmp(env_var->name, varname, len) != 0 && envdata->lst)
	{
		env_var = envdata->lst->content;
		envdata->lst = envdata->lst->next;
	}
	if (!envdata->lst)
		return (mini_errprint(ERR_DEF, DFI, DLI, DFU));
	else
	{
		ft_free (&env_var->name);
		ft_free (&env_var->value);
		free (env_var);
	}
}

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

	envdata->lst = envdata->start;
	while (envdata->lst)
	{
		env_var = envdata->lst->content;
		if (!ft_strncmp(varname, env_var->name, ft_strlen(varname)))
			return (0);
		envdata->lst = envdata->lst->next;
	}
	return (1);
}

void	mini_export_replace_var(t_envdata *envdata, char *newvar)
{
	t_env	*env_var;
	char	*varname;
	int		index;

	envdata->lst = envdata->start;
	index = ft_int_strchr(newvar, '=');
	varname = ft_substr(newvar, 0, index);
	while (envdata->lst && varname)
	{
		env_var = envdata->lst->content;
		if (!ft_strncmp(varname, env_var->name, ft_strlen(varname)))
		{
			free (env_var->value);
			env_var->value = ft_substr(newvar, index + 1, ft_strlen(newvar));
			break ;
		}
		envdata->lst = envdata->lst->next;
	}
	free (varname);
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
		{
			free (env_var->name);
			mini_export_replace_var(envdata, newvar);
		}
		else
		{
			env_var->value = ft_substr(newvar,
					ft_int_strchr(newvar, '=') + 1, ft_strlen(newvar));
			ft_lstadd_back(&envdata->lst, ft_lstnew(env_var));
			envdata->lst_size++;
		}
	}
	return (0);
}
