/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_defines.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 07:59:42 by ljohnson          #+#    #+#             */
/*   Updated: 2022/06/13 09:50:39 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_DEFINES_H
# define MINI_DEFINES_H

# include <minishell.h>

/*/////////////////////////////////////////////////////////////////////////////
		DEFINES
*//////////////////////////////////////////////////////////////////////////////

# ifndef IDT_CMD
#  define IDT_CMD 10
# endif //IDT_CMD

# ifndef IDT_BTIN
#  define IDT_BTIN 20
# endif //IDT_BTIN

# ifndef IDT_REDIR
#  define IDT_REDIR 30
# endif //IDT_REDIR

# ifndef ENVNAME_CSET
#  define ENVNAME_CSET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"
# endif //ENVNAME_CSET
#endif //MINI_DEFINES_H
