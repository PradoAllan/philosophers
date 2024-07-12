NAME = philo

CC = cc

FLAGS = -Wall -Wextra -Werror

OUT = -o $(NAME)

SOURCES = src/main.c

OBJECTS = ${SOURCES:.c=.o}

RM = rm -rf

.c.o:
	@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) $(OUT)
	@echo "\033[1;97m   All Ready to Go!   \033[0m"

all: $(NAME)

clean:
	@$(RM) $(OBJECTS)
	@echo "\033[38;2;255;165;0m   Objects Are Cleaned!   \033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[31m   Everything Is Cleaned!   \033[0m"

re: fclean all

.PHONY: all clean fclean re
