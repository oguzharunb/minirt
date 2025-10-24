NAME = minirt

# 📁 Kaynak dosyalar
SRCS = main.c
OBJS = $(SRCS:.c=.o)

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
$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

# 📦 .o dosyaları oluştur
%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

# 🧹 Temizlik hedefleri
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all
