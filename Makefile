NAME = cub3D

SRCS = main.c \
			init.c \
			file.c \
			file_params.c \
			file_map.c \
			checks.c \
			pixel_draw.c \
			game.c \
			game_changes.c \
			raycasting.c \
			raycasting_draw.c \
			sprites.c \
			utils.c \
			utils2.c \
			screenshot.c \
			exit.c \
			utils_exit.c

SRCS_BONUS = main.c \
			./bonus/init_bonus.c \
			file.c \
			file_params.c \
			file_map.c \
			checks.c \
			pixel_draw.c \
			./bonus/game_bonus.c \
			game_changes.c \
			raycasting.c \
			raycasting_draw.c \
			./bonus/sprites_bonus.c \
			./bonus/sprites_on_minimap_bonus.c \
			./bonus/minimap_bonus.c \
			utils.c \
			utils2.c \
			screenshot.c \
			exit.c \
			utils_exit.c

HEADER = ./cub.h

HEADER_BONUS = ./bonus/cub_bonus.h

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

FLAGS = -Wall -Wextra -Werror

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@make -C libft
	@make -C mlx
	cp mlx/libmlx.dylib libmlx.dylib
	@gcc -o $(NAME) $(SRCS) libft/libft.a libmlx.dylib $(FLAGS)
	./cub3D heart.cub

bonus: $(OBJS_BONUS) $(HEADER_BONUS)
	@make -C libft
	@make -C mlx
	cp mlx/libmlx.dylib libmlx.dylib
	@gcc -o $(NAME) $(SRCS_BONUS) libft/libft.a libmlx.dylib $(FLAGS)
	./cub3D labirint.cub

play: bonus
	./cub3D labirint.cub

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@make -C libft clean
	@make -C mlx clean

fclean: clean
	@rm -rf $(NAME)
	@rm libmlx.dylib
	@make -C libft fclean

re: fclean all

.PHONY:	all clean fclean re