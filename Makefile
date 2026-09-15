NAME = miniRT

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# NOTE: Adjust the path to where your libmlx.a file is located!
MLX_DIR = ./mlx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

INCLUDES = -I./includes -I$(MLX_DIR)

MATH_FLAGS = -lm

SRCS = srcs/main.c \
       srcs/mlx.c \
       srcs/render.c \
       srcs/sphere.c \
       srcs/math/adv_arith.c \
       srcs/math/basic_arith.c \
       srcs/math/helper_funcs.c \
       srcs/camera/camera.c \
       srcs/camera/ray.c \
       srcs/camera/viewport.c \
       src/parser/utils/get_next_line.c \
       src/parser/utils/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
