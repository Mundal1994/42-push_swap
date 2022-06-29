## push_swap

## ABOUT

This is a project that tests your ability to simple and highly effective create an algorithm that sort data. At your disposal you have a set of int values, 2 stacks and a set of
instructions to manipulate both stacks.

The following programs needs to be created
	The first, named checker which takes integer arguments and reads instructions on the standard output. Once read, checker executes them and displays OK if integers are sorted. Otherwise, it will display KO.
	The second one called push_swap which calculates and displays on the standard output the smallest progam using Push_swap instruction language that sorts integer arguments received.


## BASIC INSTRUCTIONS

The game is composed of 2 stacks named a and b.
At the beginning of the game

	a contains a random number of either positive or negative numbers without any duplicates.
	b is empty

Goal: sort in ascending order numbers into stack a.
Operations at your disposal:

	sa : swap a - swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements).
	sb : swap b - swap the first 2 elements at the top of stack b. Do nothing if there is only one or no elements).
	ss : sa and sb at the same time.
	pa : push a - take the first element at the top of b and put it at the top of a. Do nothing if b is empty.
	pb : push b - take the first element at the top of a and put it at the top of b. Do nothing if a is empty.
	ra : rotate a - shift up all elements of stack a by 1. The first element becomes the last one.
	rb : rotate b - shift up all elements of stack b by 1. The first element becomes the last one.
	rr : ra and rb at the same time.
	rra : reverse rotate a - shift down all elements of stack a by 1. The last element becomes the first one.
	rrb : reverse rotate b - shift down all elements of stack b by 1. The last element becomes the first one.
	rrr : rra and rrb at the same time.


## HOW TO RUN PUSH_SWAP and CHECKER

	1. make all
	2. two executables had been created: push_swap and checker
		you can run them individually or together as demonstrated below

		2a. run checker by itself
		./checker 2 1 4 3 5

		2b. run push_swap by itself
		./push_swap 2 1 4 3 5

		2c. run them together
		ARG="2 1 4 3 5"; ./push_swap $ARG | ./checker $ARG


## HOW TO RUN TEST FILES

	1. make sure the path seen at the beginning of the document is set to the path to your push_swap
	2. make sure you have a compiled version of your push_swap before running the following command.
		
		./test_file/test.sh