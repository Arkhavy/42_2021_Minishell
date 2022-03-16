/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_error_def.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:23:26 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/16 11:33:05 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_ERROR_DEF_H
# define MINI_ERROR_DEF_H

# define E_AC		"MINISHELL ERROR: No argument required\n"
# define E_MALLOC	"MINISHELL ERROR: Memory Allocation failed\n"
# define E_PIPE		"MINISHELL ERROR: Pipe function failed\n"
# define E_FORK		"MINISHELL ERROR: Fork function failed\n"
# define E_DUP		"MINISHELL ERROR: Dup function failed\n"
# define E_ACCESS_F	"MINISHELL ERROR: Could not find file\n"
# define E_ACCESS_R	"MINISHELL ERROR: Could not read file\n"
# define E_ACCESS_W	"MINISHELL ERROR: Could not write on file\n"
# define E_ACCESS_X	"MINISHELL ERROR: Could not execute file\n"
# define E_EXECVE	"MINISHELL ERROR: Execve function failed\n"
# define E_OPEN		"MINISHELL ERROR: Open function failed\n"
# define E_READ		"MINISHELL ERROR: Read function failed\n"
# define E_WRITE	"MINISHELL ERROR: Write function failed\n"
# define E_CLOSE	"MINISHELL ERROR: Close function failed\n"
# define E_HOME		"MINISHELL ERROR: Home not set\n"
# define E_CHDIR	"MINISHELL ERROR: Chdir function failed\n"
# define DFI		__FILE__
# define DLI		__LINE__
# define DFU		(char *)__FUNCTION__

#endif //MINI_ERROR_DEF_H