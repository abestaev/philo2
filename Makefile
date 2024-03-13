CC = cc

CFLAGS = -Werror -Wextra -Werror

NAME = philo

SRC = philo.c parsing.c routine.c

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