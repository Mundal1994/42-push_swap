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
SRC += $(C)instruction_solve.c
SRC += $(CO)valid_input_checker.c
SRC += $(CO)create_stack.c
SRC += $(CO)solve_stack.c
SRC += $(CO)check_if_solved.c

SRC2 = $(S)main.c
SRC2 += $(S)sort_stack.c
SRC2 += $(S)stack_rotate_init.c
SRC2 += $(S)push_and_update.c
SRC2 += $(S)longest_list.c
SRC2 += $(S)sort_parts.c
SRC2 += $(S)push_to_stack.c
SRC2 += $(S)sort_parts_helper.c
SRC2 += $(S)short_stack_logic.c
SRC2 += $(S)bonus.c
SRC2 += $(CO)valid_input_checker.c
SRC2 += $(CO)create_stack.c
SRC2 += $(CO)solve_stack.c
SRC2 += $(CO)check_if_solved.c

MAKELIB = make -C libft/ clean && make -C libft/

all: $(NAME) $(NAME2)
$(NAME): $(SRC)
	$(MAKELIB)
	$(CC) $(SRC) ./libft/libft.a -o $(NAME)
$(NAME2): $(SRC2)
	$(MAKELIB)
	$(CC) $(SRC2) ./libft/libft.a -o $(NAME2)

clean:
	/bin/rm -f *.o
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME) $(NAME2)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
