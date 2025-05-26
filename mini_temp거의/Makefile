# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/18 00:47:43 by djang             #+#    #+#              #
#    Updated: 2025/05/25 03:47:39 by djang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = src/main.c \
      src/init.c \
      src/signal.c \
      src/tokenizer.c \
      src/tokenizer2.c \
      src/tokenizer3.c \
      src/parser.c \
      src/parser2.c \
      src/parser3.c \
      src/execute.c \
      src/execute2.c \
      src/execute3.c \
      src/execute4.c \
      src/env.c \
      src/env2.c \
      src/env3.c \
      src/env4.c \
      src/builtin.c \
      src/builtin2.c \
      src/builtin3.c \
      src/builtin4.c \

OBJ = $(SRC:.c=.o)

INCLUDE = -Iincludes -Ilibft

LIBS = -lreadline -Llibft -lft

# 빌드 타겟: libft/libft.a 먼저 빌드, 그 후 minishell
all: libft/libft.a $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDE) $(LIBS) -o $(NAME)

libft/libft.a:
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
