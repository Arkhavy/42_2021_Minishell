# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:51:46 by ljohnson          #+#    #+#              #
#    Updated: 2022/05/02 10:09:05 by plavergn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re makelibft
# .SILENT:

NAME	:=	minishell
LIBFT	:=	libft/libft.a

LST_TEST		:=	display_env_main.c			display_env_minishell.c			\
					display_env_paths.c			display_envsplit_minishell.c	\
					display_errors.c			mini_display_hub.c				\
					display_export_env_test.c	display_export_unset_test.c		\
					display_cd_pwd_test.c		display_check_line_test.c
P_TEST			:=	test/

#//////////////////////////////////////////////////////////////////////////////
#		ALL FILES
#//////////////////////////////////////////////////////////////////////////////

# Files
LST_HEAD		:=	minishell.h
LST_INIT		:=	main.c					mini_init_envdata.c		mini_init_main.c
LST_MANAGERS	:=	manage_envdata_index.c	manage_envdata_vars.c	manage_envdata_lst.c
LST_PARSING		:=	parsing_main.c
LST_EXEC		:=
LST_HEREDOC		:=	ft_heredoc.c
LST_READLINE	:=	ft_readline.c		search_signal.c
LST_BUILT_IN	:=	built_in_export.c		built_in_env.c			built_in_pwd.c		\
					built_in_cd.c			built_in_unset.c		built_in_echo.c		\
					built_in_exit.c
LST_END			:=	end_of_program.c

# Directories
P_READLINE_LIB = ~/homebrew/opt/readline
P_HEAD_LIBFT	:=	libft/incs/
P_HEAD			:=	incs/
P_HEREDOC		:=	heredoc/
P_SRCS			:=	srcs/
P_INIT			:=	init/
P_MANAGERS		:=	managers/
P_PARSING		:=	parsing/
P_EXEC			:=	exec/
P_BUILT_IN		:=	built_in/
P_END			:=	end/
P_READLINE		:=	readline/
P_OBJS			:=	.objs/

# Shortcuts
HEADERS			:=	$(addprefix $(P_HEAD),$(LST_HEAD))
SRCS			:=	$(addprefix $(P_SRCS)$(P_INIT),$(LST_INIT))			\
					$(addprefix $(P_SRCS)$(P_MANAGERS),$(LST_MANAGERS))	\
					$(addprefix $(P_SRCS)$(P_PARSING),$(LST_PARSING))	\
					$(addprefix $(P_SRCS)$(P_EXEC),$(LST_EXEC))			\
					$(addprefix $(P_SRCS)$(P_BUILT_IN),$(LST_BUILT_IN))	\
					$(addprefix $(P_SRCS)$(P_END),$(LST_END))			\
					$(addprefix $(P_SRCS)$(P_READLINE),$(LST_READLINE))	\
					$(addprefix $(P_SRCS)$(P_HEREDOC),$(LST_HEREDOC))	\
					# $(addprefix $(P_SRCS)$(P_TEST),$(LST_TEST))
OBJS			:=	$(subst $(P_SRCS),$(P_OBJS),$(SRCS:.c=.o))

#//////////////////////////////////////////////////////////////////////////////
#		COMMAND SHORTCUTS
#//////////////////////////////////////////////////////////////////////////////

RLI	=	-I $(P_READLINE_LIB)/include
RLL	=	-L $(P_READLINE_LIB)/lib
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
	$(CC) $(CF) $(RLL) -lreadline $(CI) $(LIBFT) $(OBJS) -o $@

$(P_OBJS)%.o: $(P_SRCS)%.c $(HEADERS) $(LIBFT) Makefile | $(P_OBJS)
	$(CC) $(CF) $(CI) $(RLI) -c $< -o $@

$(P_OBJS):
	mkdir -p $(P_OBJS)	\
	$(P_OBJS)$(P_INIT)	$(P_OBJS)$(P_MANAGERS)	$(P_OBJS)$(P_PARSING)	$(P_OBJS)$(P_READLINE)	$(P_OBJS)$(P_HEREDOC)\
	$(P_OBJS)$(P_EXEC)	$(P_OBJS)$(P_BUILT_IN)	$(P_OBJS)$(P_END)	$(P_OBJS)$(P_TEST)

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

re:
	$(MAKE) fclean
	$(MAKE) all
