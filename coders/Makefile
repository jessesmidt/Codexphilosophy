# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jsmidt <jsmidt@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2026/03/03 20:50:46 by jsmidt        #+#    #+#                  #
#    Updated: 2026/03/20 17:15:33 by jsmidt        ########   odam.nl          #
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
			./$(NAME) 4 2000 200 200 200 5 100 fifo
			
run_edf:		
			./$(NAME) 4 2000 200 200 200 5 100 edf

run_burnout:		
			./$(NAME) 4 500 200 200 200 5 100 fifo

run_single:		
			./$(NAME) 1 800 200 200 200 5 100 fifo

test:		
			make
			./tester.sh
		
clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all run test clean fclean re