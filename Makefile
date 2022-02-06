# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaejlee <jaejlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/28 13:04:12 by jaejlee           #+#    #+#              #
#    Updated: 2021/08/20 09:15:03 by jaejlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			gcc
CFLAGS =		-Wextra -Werror -Wall -g -fsanitize=address $(addprefix -I , $(INCS))

AR =			ar
ARFLAGS =		-rcs

RM =			rm
RMFLAGS =		-rf

NAME =			minishell

SRC_DIR =		./src
INC_DIR =		./inc
LIB_DIR =		./lib

BUILTIN_DIR =	builtin
PARSE_DIR =		parse
REDIRECT_DIR =	redirect
UTIL_DIR =		util

LIB_NAMES =		Libft/libft.a

SRC_BUILTIN =	ft_cd.c \
				ft_echo.c \
				ft_env.c \
				ft_exit.c \
				ft_export.c \
				ft_pwd.c \
				ft_unset.c

SRC_PARSE =		find_path.c \
				parse_argv.c \
				parse_builtin.c \
				parse_cmd.c \
				parse_env.c \
				parse_program.c \
				parse_redirect.c \
				parse_wildcard.c

SRC_UTIL =		cmd.c \
				env_to_tree.c \
				error_guard.c \
				free_str_arr.c \
				ft_error.c \
				ft_str_del_front.c \
				ft_strcmp.c \
				ft_strjoin3.c \
				get_next_line.c \
				ms_init.c \
				tree_to_env.c \
				tree.c

SRC_FILES =		main.c \
				$(addprefix $(BUILTIN_DIR)/, $(SRC_BUILTIN)) \
				$(addprefix $(PARSE_DIR)/, $(SRC_PARSE)) \
				$(addprefix $(REDIRECT_DIR)/, $(SRC_REDIRECT)) \
				$(addprefix $(UTIL_DIR)/, $(SRC_UTIL))

SRCS =			$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS =			$(SRCS:.c=.o)
LIBS =			$(addprefix $(LIB_DIR)/, $(LIB_NAMES))
INCS =			$(dir $(LIBS)) $(INC_DIR) ${HOME}/.brew/opt/readline/include

all : $(NAME)

$(NAME) : $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) -lreadline -L${HOME}/.brew/opt/readline/lib

%.dylib :
	make -C $(dir $@)

%.a :
	make -C $(dir $@)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(RMFLAGS) $(OBJS) $(notdir $(LIBS))
	$(foreach var, $(LIBS), make clean -C $(dir $(var));)

fclean : clean
	$(RM) $(RMFLAGS) $(NAME)
	$(foreach var, $(LIBS), make fclean -C $(dir $(var));)

re : fclean all
bonus : all

.PHONY : bonus all clean fclean re
