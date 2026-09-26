NAME = miniRT

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ./mlx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

INCLUDES = -I./includes -I$(MLX_DIR) -I$(LIBFT_DIR)

MATH_FLAGS = -lm

SRCS = srcs/main.c \
       srcs/mlx.c \
       srcs/render.c \
       srcs/sphere.c \
       srcs/plane.c \
       srcs/cylinder.c \
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
       srcs/parser/utils/utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
