NAME = cub3D

SRCS = *.c

HEADER = ./cub.h

OBJS = $(SRCS:.c=.o)

#-Wall -Wextra -Werror
FLAGS = libmlx.dylib -framework OpenGL -framework AppKit

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	
test: $(OBJS) $(HEADER)
	@gcc -g $(SRCS) libft/libft.a $(FLAGS)

clean:
	@rm -rf $(OBJS)
	@make -C libft clean
	@make -C mlx clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean

re: fclean all

play: all
	@./$(NAME) map.cub

screenshot: all
	@./$(NAME) map.cub --save

.PHONY:	all clean fclean re