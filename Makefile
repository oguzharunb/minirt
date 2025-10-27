NAME = minirt
TEST_NAME = minirt_test
# 📁 Kaynak dosyalar
SRCS = ray.c camera.c color.c sphere.c vector_calc.c vector.c
MAIN = main.c
TEST = test.c
MAIN_OBJS = $(SRCS:.c=.o) main.o
TEST_OBJS = $(SRCS:.c=.o) test.o

# ⚙️ Derleyici ve bayraklar
CC = cc
CFLAGS = -Wall -Wextra -Werror

# 🧱 MiniLibX ayarları
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# 🎯 Varsayılan hedef
all: $(NAME)

# 🔨 Derleme
$(NAME): $(MAIN_OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN_OBJS) $(MLX_FLAGS)

# 🔨 Derleme
test: $(TEST_OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(TEST_NAME) $(TEST_OBJS) $(MLX_FLAGS)

# 📦 .o dosyaları oluştur
%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

# 🧹 Temizlik hedefleri
clean:
	rm -f $(MAIN_OBJS) $(TEST_OBJS)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all
