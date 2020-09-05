# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/30 22:32:54 by kallard           #+#    #+#              #
#    Updated: 2020/08/31 18:47:47 by kallard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = main.c

HEADER = ./cub3D.h

OBJS = $(SRCS:.c=.o)

#-Wall -Wextra -Werror
FLAGS = -Wall -Werror -Wextra -fsanitize=address -Lmlx -lmlx -framework OpenGL -framework AppKit

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	
$(NAME): $(OBJS) $(HEADER)
	@make -C libft
	@make -C minilibx
	@gcc -o $(NAME) $(OBJS) libft/*.o minilibx/libmlx.a $(FLAGS)

all: $(NAME)

clean:
	@rm -rf $(OBJS)
	@make -C libft clean
	@make -C minilibx clean

# также надо будет удалить скриншот
fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean

re: fclean all

play: all
	@./$(NAME) map.cub

screenshot: all
	@./$(NAME) map.cub --save

.PHONY:	all clean fclean re