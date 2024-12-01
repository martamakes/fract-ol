# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 17:45:41 by mvigara-          #+#    #+#              #
#    Updated: 2024/12/01 10:21:34 by mvigara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include -I./lib/MLX42/include -I./lib/libft/inc

# Detect the operating system
UNAME_S := $(shell uname -s)

# Directories
SRC_DIR = src
OBJ_DIR = obj
MLX_DIR = lib/MLX42
MLX_BUILD = $(MLX_DIR)/build
MLX_INIT_MARK = $(MLX_DIR)/.init_done

# macOS specific configuration
ifeq ($(UNAME_S),Darwin)
    LDFLAGS = -L$(MLX_BUILD) -lmlx42 -L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw \
              -framework Cocoa -framework OpenGL -framework IOKit -lm
endif

# Linux specific configuration
ifeq ($(UNAME_S),Linux)
    LDFLAGS = -L$(MLX_BUILD) -lmlx42 -lglfw -lm -ldl -pthread
endif

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

NAME = fractol

# Main rules
all: $(MLX_INIT_MARK) $(NAME)

$(MLX_INIT_MARK):
	@echo "\033[0;33mInitializing MLX42 submodule...\033[0m"
	@git submodule update --init --recursive
	@cmake -B $(MLX_BUILD) $(MLX_DIR) >/dev/null 2>&1
	@$(MAKE) -C $(MLX_BUILD) >/dev/null 2>&1
	@touch $(MLX_INIT_MARK)

$(NAME): $(OBJS)
	@$(MAKE) -C lib/libft
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LDFLAGS) lib/libft/libft.a
	@echo "\033[0;32mfractol compiled!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Creating directory: $(dir $@)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Cleaning rules
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C lib/libft clean
	@echo "\033[0;31mObject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C lib/libft fclean
	@rm -rf $(MLX_BUILD)
	@rm -f $(MLX_INIT_MARK)
	@echo "\033[0;31mExecutables removed\033[0m"

re: fclean all

.PHONY: all clean fclean re