# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iheaders -Ilibft
LDFLAGS = -lreadline

# Directories
UTILS_DIR = utils
TOKENIZER_DIR = tokenizer
LIBFT_DIR = libft
OBJ_DIR = objects

# Source files
SRCS = main.c prompt.c \
	$(UTILS_DIR)/bool_utils.c \
	$(UTILS_DIR)/clean_exit.c \
	$(UTILS_DIR)/linked_list_utils.c \
	$(UTILS_DIR)/parsing_utils.c \
	$(UTILS_DIR)/string_utils.c \
	$(TOKENIZER_DIR)/tokenizer.c \
	$(TOKENIZER_DIR)/split2.c \
	$(TOKENIZER_DIR)/refine_token.c

# Create list of object files in the objects/ dir
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Executable name
NAME = lexer

# Default target
all: $(NAME)

# Link everything into the final executable
$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/libft.a -o $(NAME) $(LDFLAGS)

# Compile .c files into objects/ path
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

# Full clean
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# Rebuild all
re: fclean all

.PHONY: all clean fclean re
