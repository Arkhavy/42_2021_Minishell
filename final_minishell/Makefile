# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/06 15:59:54 by ljohnson          #+#    #+#              #
#    Updated: 2022/05/06 16:45:57 by ljohnson         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re makelibft
# .SILENT:

NAME			:=	minishell
LIBFT			:=	libft/libft.a

#//////////////////////////////////////////////////////////////////////////////
#		ALL FILES
#//////////////////////////////////////////////////////////////////////////////

# Files
LST_HEAD		:=	minishell.h
LST_INIT		:=	
LST_MANAGERS	:=
LST_PARSING		:=
LST_EXECUTION	:=
LST_BUILT_IN	:=
LST_PROMPT		:=

# Directories
P_READLINE_LIB	:=	~/homebrew/opt/readline
P_HEAD_LIBFT	:=	libft/incs/
P_HEAD			:=	incs/
P_SRCS			:=	srcs/

P_BUILT_IN		:=	built_in/
P_EXECUTION		:=	execution/
P_INIT			:=	init/
P_MANAGERS		:=	managers/
P_PARSING		:=	parsing/
P_PROMPT		:=	prompt/

P_OBJS			:=	.objs/

# Shortcuts
INCS			:=	$(addprefix $(P_HEAD),$(LST_HEAD))
					$(addprefix $(P_SRCS)$(P_BUILT_IN),$(LST_BUILT_IN))		\
					$(addprefix $(P_SRCS)$(P_EXECUTION),$(LST_EXECUTION))	\
SRCS			:=	$(addprefix $(P_SRCS)$(P_INIT),$(LST_INIT))				\
					$(addprefix $(P_SRCS)$(P_MANAGERS),$(LST_MANAGERS))		\
					$(addprefix $(P_SRCS)$(P_PARSING),$(LST_PARSING))		\
					$(addprefix $(P_SRCS)$(P_PROMPT),$(LST_PROMPT))			\
					$(addprefix $(P_SRCS),main.c)
OBJS			:=	$(subst $(P_SRCS),$(P_OBJS),$(SRCS:.c=.o))