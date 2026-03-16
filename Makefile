# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jsmidt <jsmidt@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2026/03/03 20:50:46 by jsmidt        #+#    #+#                  #
#    Updated: 2026/03/16 21:36:05 by jsmidt        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= codexion
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -pthread

SRC_DIR = src
OBJ_DIR = obj

SRC = cleanup.c \
	  coder_routine.c \
	  heap.c \
	  init.c \
	  main.c \
	  monitoring.c \
      parsing.c \
	  simulation.c \
	  utility.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJ  = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all:		$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run:		
			./$(NAME) 1 1200 200 200 200 5 100 edf

test:		
			make
			./tester.sh
		
clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all run test clean fclean re