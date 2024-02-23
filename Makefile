# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobert <trobert@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/17 15:56:46 by trobert           #+#    #+#              #
#    Updated: 2022/10/25 16:01:55 by trobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	./main/main.c\
		./main/init_minishell.c\
		./main/init_var.c\
		./main/init_env.c\
		./parsing/get_in_lst.c\
		./parsing/parsing_utils.c\
		./parsing/find_var_exp.c\
		./parsing/clean_lst_arg.c\
		./parsing/clean_lst_expand.c\
		./parsing/join_lst_arg.c\
		./parsing/parse_block.c\
		./parsing/block_utils.c\
		./parsing/set_tokens.c\
		./check_syntax/check_syntax_error.c\
		./check_syntax/check_metachar.c\
		./check_syntax/check_syntax_utils.c\
		./check_syntax/check_first_last_pipe.c\
		./exec/get_cmd_execve.c\
		./exec/pipex.c\
		./exec/pipex_utils.c\
		./exec/init_pipex.c\
		./exec/execve_pipex.c\
		./exec/exec_one_builtin.c\
		./exec/close_pipes.c\
		./io_redir/open_all_files.c\
		./io_redir/openfile_functions.c\
		./io_redir/close_all_files.c\
		./io_redir/here_doc.c\
		./io_redir/here_doc_error.c\
		./io_redir/io_redir_utils.c\
		./builtins/echo.c\
		./builtins/pwd.c\
		./builtins/env.c\
		./builtins/cd.c\
		./builtins/cd_utils.c\
		./builtins/cd_utils2.c\
		./builtins/export.c\
		./builtins/export_utils.c\
		./builtins/export_utils2.c\
		./builtins/export_utils3.c\
		./builtins/export_utils4.c\
		./builtins/export_utils5.c\
		./builtins/unset.c\
		./builtins/exit.c\
		./builtins/exit_utils.c\
		./builtins/builtins_utils.c\
		./libft/libft_utils.c\
		./libft/libft_utils2.c\
		./libft/libft_utils3.c\
		./libft/ft_split.c\
		./libft/ft_split_quote.c\
		./libft/lst_functions.c\
		./libft/ft_itoa.c\
		./gc/godmalloc.c\
		./gc/godmalloc_utils.c\
		./gc/godmalloc_utils_2.c\
		./gc/godmalloc_utils_3.c\
		./gc/godmalloc_utils_4.c\
		./gc/free_malloc.c\
		./signal/signals.c\
		./utils/free_functions.c\
		./utils/free_functions2.c\
		./utils/printing_utils.c\
		./utils/printing_utils2.c\
		./utils/printing_utils3.c\
		./utils/printing_utils4.c\

SRCS = ${addprefix srcs/, ${SRC}}

OBJS = ${SRCS:.c=.o}

INC = -I./includes

CC = cc -g

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

RLFLAGS = -lreadline

all: ${NAME}

${NAME}: ${OBJS} includes/minishell.h
	${CC} ${CFLAGS} ${OBJS} ${INC} -o ${NAME} ${RLFLAGS}

.c.o:
	${CC} ${CFLAGS} ${INC} -c $< -o ${<:.c=.o}

clean:
	${RM} ${OBJS} ${BOBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: clean fclean bonus all re
