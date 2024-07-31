CC = cc

CFLAGS = -Werror -Wextra -Werror

NAME = philo

SRC = src/main.c src/parsing.c src/routine.c src/utils.c src/init.c \
	src/time.c #src/threads.c 

HEADER = -I include

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o:%.c
			$(CC) $(CFLAGS) -o $@ -c $< $(HEADER)

$(NAME): $(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(HEADER)

clean:
			rm -rf $(OBJ)

fclean:	clean
			rm $(NAME)
re: fclean all

.PHONY: all clean fclean re