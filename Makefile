# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molesen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 16:06:38 by molesen           #+#    #+#              #
#    Updated: 2022/05/09 16:06:42 by molesen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = checker
NAME2 = push_swap

CC = gcc -Wall -Wextra -Werror

C = check/
S = swap/
CO = common/

SRC = $(C)main.c
SRC += $(C)instruction_check.c
SRC += $(C)solve_stack.c
SRC += $(CO)valid_input_checker.c
SRC += $(CO)create_stack.c

SRC2 = $(S)main.c
SRC2 += $(CO)valid_input_checker.c
SRC2 += $(CO)create_stack.c

MAKELIB = make -C libft/ fclean && make -C libft/

all: $(NAME) $(NAME2)
$(NAME):
	$(MAKELIB)
	$(CC) -o $(NAME) $(SRC) ./libft/libft.a
$(NAME2):
	$(CC) -o $(NAME2) $(SRC2) ./libft/libft.a

clean:
	/bin/rm -f *.o
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME) $(NAME2)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
