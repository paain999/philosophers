# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dajimene <dajimene@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/28 22:38:24 by dajimene          #+#    #+#              #
#    Updated: 2024/04/30 10:26:53 by dajimene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f
RM_DIR = rm -rf

INCLUDE = -I include/
OBJ_DIR = obj/
SRC_DIR = src/

SRC_FILES = ${shell find src/ -name "*.c"}

SRC = $(SRC_FILES)
OBJ = $(subst src/, obj/, $(SRC))
OBJS = $(OBJ:.c=.o)

.SILENT:

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)
	echo "\033[1;33mCompiling Philosophers" && echo "." && sleep 0.6 && echo "." && sleep 0.6 && echo "." && sleep 0.4
	echo "\033[33m\n Welcome to the...\n \033[0m"
	echo "\033[36m██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗\033[0m"
	echo "\033[36m██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝\033[0m"
	echo "\033[36m██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗\033[0m"
	echo "\033[36m██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║\033[0m"
	echo "\033[36m██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║\033[0m"
	echo "\033[36m╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\033[0m"
	echo "\n"
	echo "\033[33m To run the program, type:\033[1;32m ./philo [philo_number] [time_to_die] [time_to_eat] [time_to_sleep] [number of meals]\033[0m"
	echo "\033[33m Example: ./philo 5 800 200 200 5 \033[0m"

valgrind_race: re
	@echo "\033[1;33m\nChecking for race conditions with valgrind...\033[0m"
	valgrind --tool=helgrind ./$(NAME) 5 800 200 200 5

valgrind_leaks: re
	@echo "\033[1;33m\nChecking for memory leaks with valgrind...\033[0m"
	valgrind --leak-check=full ./$(NAME) 5 800 200 200 5

clean:
	@$(RM) $(OBJS)
	@$(RM_DIR) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[1;31mCleaning up...\033[0m" && sleep 1
	@echo "\033[1;32mAll cleaned up!\033[0m"

re: fclean all

.PHONY: all clean fclean re
