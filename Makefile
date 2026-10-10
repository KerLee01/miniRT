NAME = miniRT
NAME_BONUS = miniRT_bonus

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ./mlx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

MATH_FLAGS = -lm

INCLUDES = -I./includes -I$(MLX_DIR) -I$(LIBFT_DIR)
INCLUDES_BONUS = -I./bonus/includes -I$(MLX_DIR) -I$(LIBFT_DIR)

SRCS = srcs/main.c \
       srcs/mlx.c \
       srcs/render/render.c \
       srcs/render/sphere.c \
       srcs/render/plane.c \
       srcs/render/cylinder.c \
       srcs/render/lighting.c \
       srcs/render/shadow.c \
       srcs/math/adv_arith.c \
       srcs/math/basic_arith.c \
       srcs/math/helper_funcs.c \
       srcs/camera/camera.c \
       srcs/camera/ray.c \
       srcs/camera/viewport.c \
       srcs/parser/parser.c \
       srcs/parser/fill_elements.c \
       srcs/parser/fill_sphere.c \
       srcs/parser/fill_plane.c \
       srcs/parser/fill_cylinder.c \
       srcs/parser/utils/get_next_line.c \
       srcs/parser/utils/get_next_line_utils.c \
       srcs/parser/utils/utils.c \
       srcs/parser/utils/parse_helpers.c

SRCS_BONUS = bonus/srcs/main_bonus.c \
             bonus/srcs/mlx_bonus.c \
             bonus/srcs/render/render_bonus.c \
             bonus/srcs/render/sphere_bonus.c \
             bonus/srcs/render/plane_bonus.c \
             bonus/srcs/render/cylinder_bonus.c \
             bonus/srcs/render/lighting_bonus.c \
             bonus/srcs/render/shadow_bonus.c \
             bonus/srcs/math/adv_arith_bonus.c \
             bonus/srcs/math/basic_arith_bonus.c \
             bonus/srcs/math/helper_funcs_bonus.c \
             bonus/srcs/camera/camera_bonus.c \
             bonus/srcs/camera/ray_bonus.c \
             bonus/srcs/camera/viewport_bonus.c \
             bonus/srcs/parser/parser_bonus.c \
             bonus/srcs/parser/fill_elements_bonus.c \
             bonus/srcs/parser/fill_sphere_bonus.c \
             bonus/srcs/parser/fill_plane_bonus.c \
             bonus/srcs/parser/fill_cylinder_bonus.c \
             bonus/srcs/parser/utils/get_next_line_bonus.c \
             bonus/srcs/parser/utils/get_next_line_utils_bonus.c \
             bonus/srcs/parser/utils/utils_bonus.c \
             bonus/srcs/parser/utils/parse_helpers_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES_BONUS) $(OBJS_BONUS) $(LIBFT) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME_BONUS)

srcs/%.o: srcs/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus/srcs/%.o: bonus/srcs/%.c
	$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
