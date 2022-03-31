# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:51:46 by ljohnson          #+#    #+#              #
#    Updated: 2022/03/31 13:07:45 by ljohnson         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re makelibft
# .SILENT:

NAME	:=	minishell
LIBFT	:=	libft/libft.a

#//////////////////////////////////////////////////////////////////////////////
#		ALL FILES
#//////////////////////////////////////////////////////////////////////////////

# Files
LST_HEAD		:=	minishell.h
LST_INIT		:=	main.c	mini_init_envdata.c	mini_init_main.c
LST_MANAGERS	:=	manage_envdata_index.c	manage_envdata_vars.c
LST_PARSING		:=	
LST_EXEC		:=	
LST_BUILT_IN	:=	built_in_export.c
LST_END			:=	end_of_program.c

# Directories
P_HEAD_LIBFT	:=	libft/lib_includes/
P_HEAD			:=	incs/
P_SRCS			:=	srcs/
P_INIT			:=	init/
P_MANAGERS		:=	managers/
P_PARSING		:=	parsing/
P_EXEC			:=	exec/
P_BUILT_IN		:=	built_in/
P_END			:=	end/
P_OBJS			:=	.objs/

# Shortcuts
HEADERS			:=	$(addprefix $(P_HEAD),$(LST_HEAD))
SRCS			:=	$(addprefix $(P_SRCS)$(P_INIT),$(LST_INIT))			\
					$(addprefix $(P_SRCS)$(P_MANAGERS),$(LST_MANAGERS))	\
					$(addprefix $(P_SRCS)$(P_PARSING),$(LST_PARSING))	\
					$(addprefix $(P_SRCS)$(P_EXEC),$(LST_EXEC))			\
					$(addprefix $(P_SRCS)$(P_BUILT_IN),$(LST_BUILT_IN))	\
					$(addprefix $(P_SRCS)$(P_END),$(LST_END))
OBJS			:=	$(subst $(P_SRCS),$(P_OBJS),$(SRCS:.c=.o))

#//////////////////////////////////////////////////////////////////////////////
#		COMMAND SHORTCUTS
#//////////////////////////////////////////////////////////////////////////////

CC				:=	gcc
CF				:=	-Wall -Wextra -Werror
CI				:=	-I $(P_HEAD) -I $(P_HEAD_LIBFT)
CS				:=	-g3 -fsanitize=address
CG				:=	-g3

RM				:=	rm -rf

#//////////////////////////////////////////////////////////////////////////////
#		RULES
#//////////////////////////////////////////////////////////////////////////////

all: makelibft $(NAME)

# Binary creation
$(NAME): $(OBJS) $(HEADERS) $(LIBFT) Makefile
	$(CC) $(CF) $(CI) $(LIBFT) $(OBJS) -o $@

$(P_OBJS)%.o: $(P_SRCS)%.c $(HEADERS) $(LIBFT) Makefile | $(P_OBJS)
	$(CC) $(CF) $(CI) -c $< -o $@

$(P_OBJS):
	mkdir -p $(P_OBJS)	\
	$(P_OBJS)$(P_INIT)	$(P_OBJS)$(P_MANAGERS)	$(P_OBJS)$(P_PARSING)	\
	$(P_OBJS)$(P_EXEC)	$(P_OBJS)$(P_BUILT_IN)	$(P_OBJS)$(P_END)

# Libft creation
$(LIBFT): makelibft

makelibft:
	$(MAKE) -j 3 -C libft/

# Mandatory rules
clean:
	$(RM) $(OBJS)
	$(RM) $(P_OBJS)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft/

re: fclean all