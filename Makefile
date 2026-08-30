NAME = miniRT

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# NOTE: Adjust the path to where your libmlx.a file is located!
MLX_DIR = ./mlx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

MATH_FLAGS = -lm

SRCS = main.c \
       mlx.c \
       render.c \
       sphere.c \
       math/adv_arith.c \
       math/basic_arith.c \
       math/helper_funcs.c \
       camera/camera.c \
       camera/ray.c \
       camera/viewport.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
