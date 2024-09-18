GREEN = \033[0;32m
RESET = \033[0m

CC = cc
CFLAGS = -Werror -Wextra -Werror -I include -pthread -g3

NAME = philo

SRC = src/main.c src/parsing.c src/routine.c src/utils.c src/time.c \
	src/thread.c src/buffer.c

OBJ_DIR = obj

OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
			@$(CC) -o $(NAME) $(OBJ)
			@echo "$(GREEN)successfully compiled$(RESET)"

clean:
			@rm -rf $(OBJ)
			@echo "Object files cleaned"

fclean:	clean
			@rm -f $(NAME)
			@echo "Executable $(NAME) removed"

re: fclean all

.PHONY: all clean fclean re