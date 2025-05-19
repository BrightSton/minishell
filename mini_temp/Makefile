# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/18 00:47:43 by djang             #+#    #+#              #
#    Updated: 2025/05/18 00:47:44 by djang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = src/main.c src/init.c src/signal.c src/tokenizer.c src/parser.c \
src/execute.c
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
