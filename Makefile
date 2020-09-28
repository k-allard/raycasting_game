NAME = cub3D

SRCS = srcs/main.c \
			srcs/init.c \
			srcs/file.c \
			srcs/file_params.c \
			srcs/file_map.c \
			srcs/checks.c \
			srcs/pixel_draw.c \
			srcs/game.c \
			srcs/game_changes.c \
			srcs/raycasting.c \
			srcs/raycasting_draw.c \
			srcs/sprites.c \
			srcs/utils.c \
			srcs/utils2.c \
			srcs/screenshot.c \
			srcs/exit.c \
			srcs/utils_exit.c

SRCS_BONUS = srcs/main.c \
			bonus/init_bonus.c \
			srcs/file.c \
			srcs/file_params.c \
			srcs/file_map.c \
			srcs/checks.c \
			srcs/pixel_draw.c \
			bonus/game_bonus.c \
			srcs/game_changes.c \
			srcs/raycasting.c \
			srcs/raycasting_draw.c \
			bonus/sprites_bonus.c \
			bonus/sprites_on_minimap_bonus.c \
			bonus/minimap_bonus.c \
			bonus/coin_counter_bonus.c \
			srcs/utils.c \
			srcs/utils2.c \
			srcs/screenshot.c \
			srcs/exit.c \
			srcs/utils_exit.c

HEADER = ./cub.h

HEADER_BONUS = bonus/cub_bonus.h

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

FLAGS = -Wall -Wextra -Werror

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@echo "\x1b[33m Preparing Cub3D...\x1b[0m"
	@make -C libft
	@make -C mlx
	cp mlx/libmlx.dylib libmlx.dylib
	@gcc -o $(NAME) $(SRCS) libft/libft.a libmlx.dylib $(FLAGS)
	@echo "\x1b[33m Cub3D is ready!\x1b[0m"
	@echo "\x1b[5;32m TYPE MAKE TEST\x1b[0m"

test: all
	./cub3D maps/heart.cub

bonus: $(OBJS_BONUS) $(HEADER_BONUS)
	@echo "\x1b[33m Preparing game...\x1b[0m"
	@make -C libft
	@make -C mlx
	cp mlx/libmlx.dylib libmlx.dylib
	@gcc -o $(NAME) $(SRCS_BONUS) libft/libft.a libmlx.dylib $(FLAGS)
	@echo "\x1b[33m Game is ready!\x1b[0m"
	@echo "\x1b[5;32m TYPE MAKE PLAY\x1b[0m"

play: bonus
	@./cub3D maps/labirint.cub

screenshot:
	@./cub3D maps/heart.cub --save

screenshot_bonus:
	@./cub3D maps/labirint.cub --save

norm:
	@echo "\x1b[33m Sources, headers, bonuses, libft NORM CHECK...\x1b[0m"
	@norminette srcs cub.h libft/*.c bonus
clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@make -C libft clean
	@make -C mlx clean

fclean: clean
	@rm -rf screenshot.bmp $(NAME)
	@rm libmlx.dylib
	@make -C libft fclean

re: fclean all

.PHONY:	all clean fclean re