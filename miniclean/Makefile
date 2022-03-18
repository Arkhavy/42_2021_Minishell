# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 10:18:12 by ljohnson          #+#    #+#              #
#    Updated: 2022/03/18 09:27:25 by ljohnson         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re makelibft
# .SILENT:

NAME			:=	minishell
UNIT			:=	mini_unit_test
LIBFT			:=	libft/libft.a

#//////////////////////////////////////////////////////////////////////////////
#		ALL FILES
#//////////////////////////////////////////////////////////////////////////////

# Files
LST_HEAD		:=	minishell_test.h
LST_BUILT_IN	:=	built_in_cd.c			built_in_echo.c		built_in_env.c	\
					built_in_exit.c			built_in_export.c	built_in_pwd.c	\
					built_in_unset.c
LST_SRC			:=	mini_env_manager.c		mini_init.c			mini_workers.c

LST_MAIN		:=	minishell.c
LST_UNIT		:=	main_unit_test.c

# Directories
P_HEAD_LIBFT	:=	libft/lib_includes/
P_HEAD			:=	mini_inc/
P_SRC			:=	mini_src/
P_UTILS			:=	mini_utils/
P_BUILT_IN		:=	mini_built_in/
P_OBJ			:=	.mini_obj/

# Shortcuts
SRCS_MAIN		:=	$(addprefix $(P_SRC)$(P_UTILS),$(LST_SRC))			\
					$(addprefix $(P_SRC)$(P_UTILS),$(LST_MAIN))			\
					$(addprefix $(P_SRC)$(P_BUILT_IN),$(LST_BUILT_IN))

SRCS_UNIT		:=	$(addprefix $(P_SRC)$(P_UTILS),$(LST_SRC))			\
					$(addprefix $(P_SRC)$(P_UTILS),$(LST_UNIT))			\
					$(addprefix $(P_SRC)$(P_BUILT_IN),$(LST_BUILT_IN))

HEADERS			:=	$(addprefix $(P_HEAD),$(LST_HEAD))
OBJS_MAIN		:=	$(subst $(P_SRC),$(P_OBJ),$(SRCS_MAIN:.c=.o))
OBJS_UNIT		:=	$(subst $(P_SRC),$(P_OBJ),$(SRCS_UNIT:.c=.o))

SRCS			:=	$(SRCS_MAIN) $(SRCS_UNIT)
OBJS			:=	$(OBJS_MAIN) $(OBJS_UNIT)

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

all: makelibft $(NAME) $(UNIT)

# Binary creation
$(NAME): $(OBJS_MAIN) $(HEADERS) $(LIBFT) Makefile
	$(CC) $(CF) $(CI) $(LIBFT) $(OBJS_MAIN) -o $@

$(UNIT): $(OBJS_UNIT) $(HEADERS) $(LIBFT) Makefile
	$(CC) $(CF) $(CI) $(CS) $(LIBFT) $(OBJS_UNIT) -o $@

$(P_OBJ)%.o: $(P_SRC)%.c $(HEADERS) $(LIBFT) Makefile
	$(CC) $(CF) $(CI) -c $< -o $@

$(OBJS): $(P_OBJ)

$(P_OBJ):
	mkdir -p $(P_OBJ)	$(P_OBJ)mini_utils/	$(P_OBJ)mini_built_in/

# Libft creation
$(LIBFT): makelibft

makelibft:
	$(MAKE) -j 3 -C libft/

# Mandatory rules
clean:
	$(RM) $(OBJS_MAIN)
	$(RM) $(OBJS_UNIT)
	$(RM) $(P_OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(UNIT)
	$(MAKE) fclean -C libft/

re: fclean all