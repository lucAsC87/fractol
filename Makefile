# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucavall <lucavall@student.42firenze.it    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 12:23:02 by lucavall          #+#    #+#              #
#    Updated: 2024/03/23 16:37:16 by lucavall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --VARIABLES--
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I./minilibx-linux
FRACTOL		= fractol
MINILIBX	= ./minilibx-linux/libmlx_Linux.a
MINILIBX_URL = https://cdn.intra.42.fr/document/document/24001/minilibx-linux.tgz
RM			= rm -rf
SRC			= fractol.c events.c ft_utils.c render.c
OBJ			= $(SRC:.c=.o)

# --RULES--

all: $(FRACTOL)

%.o: %.c $(MINILIBX)
	$(CC) $(CFLAGS) -c $< -o $@

$(MINILIBX):
	@if [ ! -d "./minilibx-linux" ]; then \
        wget -O minilibx-linux.tgz $(MINILIBX_URL); \
        tar -xzf minilibx-linux.tgz; \
		make -C ./minilibx-linux; \
	fi

$(FRACTOL): $(OBJ) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX) -o $(FRACTOL) -lm -lX11 -lXext

clean:
	@make clean -C ./minilibx-linux
	$(RM) $(OBJ) minilibx-linux.tgz

fclean: clean
	$(RM) $(FRACTOL)
	$(RM) $(MINILIBX)

re: fclean all

.PHONY: all clean fclean re
