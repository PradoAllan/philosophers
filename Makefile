NAME = philo

CC = cc

THREADS = -pthread

FLAGS = -Wall -Wextra -Werror

OUT = -o $(NAME)

SOURCES = src/main.c \
	  src/validate_input.c \
	  src/utils.c \
	  src/linked_list.c \
	  src/free_functions.c \
	  src/simulation.c \
	  src/arbitrator_utils.c

OBJECTS = ${SOURCES:.c=.o}

RM = rm -rf

.c.o:
	@$(CC) $(THREAD) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJECTS) progress
	@$(CC) $(FLAGS) $(OBJECTS) $(OUT)
	@sleep 0.2
	@printf "\033[0;32m ALL READY TO GO!\033[0m\n"; \

all: $(NAME)

clean:
	@$(RM) $(OBJECTS)
	@sleep 0.1
	@printf "\033[0;32m OBJECTS CLEANED!\033[0m\n"; \

fclean: clean
	@$(RM) $(NAME)
	@sleep 0.1
	@printf "\033[0;32m ALL CLEANED!\033[0m\n"; \

re: fclean all

progress:
	@$(MAKE) --no-print-directory _progress

_progress:
	@tput civis
	@width=50; \
	progress=0; \
	while [ $$progress -le $$width ]; do \
		printf "\r\033[0;32m Progress: [ "; \
		for i in $$(seq 1 $$progress); do \
			printf "="; \
		done; \
		for i in $$(seq $$progress $$width); do \
			printf " "; \
		done; \
		percent=$$((progress * 2)); \
		printf "]%d%%\033[0m" $$percent; \
		progress=$$((progress + 5)); \
		sleep 0.1; \
	done; \
	printf "\n\033[0;32m COMPILATION COMPLETE!\033[0m\n"; \
	tput cnorm

.PHONY: all clean fclean re
