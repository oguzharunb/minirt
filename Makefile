NAME        = minirt
TEST_NAME   = minirt_test

LIBFT_DIR   = ./libft
GNL_DIR     = ./gnl
MLX_DIR     = ./minilibx-linux

LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

GNL_SRCS    = $(GNL_DIR)/get_next_line.c \
              $(GNL_DIR)/get_next_line_utils.c

SRCS        = ray.c color.c render.c sphere.c vector.c plane.c \
              shading_utils.c mlx_utils.c lighting_utils.c shadow_utils.c \
              cylinder.c parser.c parser_utils.c \
              $(GNL_SRCS)

OBJS        = $(SRCS:.c=.o)
MAIN_OBJ    = main.o
TEST_OBJ    = test.o

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
INCLUDES    = -I. -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
# macOS MiniLibX flags
#MLX_FLAGS   = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
LIBS        = -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@echo "Compiling Libft..."
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@echo "Compiling MiniLibX (macOS)..."
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(MAIN_OBJ) $(LIBFT) $(MLX)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) $(LIBS) -o $(NAME)

test: $(OBJS) $(TEST_OBJ) $(LIBFT) $(MLX)
	@echo "Linking $(TEST_NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(TEST_OBJ) $(LIBS) -o $(TEST_NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning objects..."
	rm -f $(OBJS) $(MAIN_OBJ) $(TEST_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@echo "Cleaning executables..."
	rm -f $(NAME) $(TEST_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test
