NAME = cub3D

SRCS = *.c ./bonus/*.c

HEADER = ./cub.h

OBJS = $(SRCS:.c=.o)

#-Wall -Wextra -Werror -g -fsanitize=address libmlx.dylib -framework OpenGL -framework AppKit
FLAGS = -g -Wall -Wextra -Werror

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	
test: $(OBJS) $(HEADER)
	@make -C libft
	@make -C mlx
	cp mlx/libmlx.dylib libmlx.dylib
	@gcc $(SRCS) libft/libft.a libmlx.dylib $(FLAGS)
	./a.out map.cub

save: $(OBJS) $(HEADER)
	@make -C libft
	@make -C mlx
	cp mlx/libmlx.dylib libmlx.dylib
	@gcc $(SRCS) libft/libft.a mlx/libmlx.dylib $(FLAGS)
	./a.out map.cub --save

clean:
	@rm -rf $(OBJS)
	@make -C libft clean
	@make -C mlx clean

fclean: clean
	@rm -rf $(NAME)
	@rm libmlx.dylib
	@make -C libft fclean

re: fclean all

play: all
	@./$(NAME) map.cub

screenshot: all
	@./$(NAME) map.cub --save

.PHONY:	all clean fclean re