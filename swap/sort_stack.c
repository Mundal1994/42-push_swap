/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:23:32 by molesen           #+#    #+#             */
/*   Updated: 2022/05/18 10:23:34 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	checks_order(t_stack *stack, int i, char c_char, int end)
{
	if (end == FALSE)
	{
		if (stack->a[i] < stack->a[i - 1] && c_char == 'a')
		{
			/*if (i > stack->median && (i > (((stack->bottom - stack->top_a) / 2) + ((stack->bottom - stack->top_a) % 2))) && stack->bottom - stack->top_a > 5)
			{
				
				stack->median = i - stack->top_a;
				stack->median_nbr = stack->a[stack->top_a + stack->median - 1];
				// ft_printf("i: %d\n", i - stack->top_a - 1);
				// ft_printf("medan: %d, median_nbr: %d\n", stack->median, stack->median_nbr);
			}*/
			return (ERROR);
		}
		else if (stack->b[i] > stack->b[i - 1] && c_char == 'b')
			return (ERROR);
	}
	else
	{
		if (stack->a[stack->bottom - 1] > stack->a[stack->top_a] && c_char == 'a')
			return (ERROR);
		if (stack->b[stack->bottom - 1] < stack->b[stack->top_b] && c_char == 'b')
			return (ERROR);
	}
	return (TRUE);
}

static int	error_start_nbr(t_stack *stack, int i, char c)
{
	stack->start_nbr = i;
	if (c == 'e')
		return (ERROR);
	else
		return (TRUE);
}

static int	check_if_ordered(t_stack *stack, int *c, int top_c, int c_char)
{
	int	i;

	i = top_c;
	while (i < stack->bottom && ((c[i] != stack->a_small && c_char == 'a') || \
	(c[i] != stack->b_big && c_char == 'b')))
		++i;
	// ft_printf("error\nasmall: %d, i: %d, top_c: %d\n", stack->a_small, i, top_c);
	// ft_printf("error\nbsmall: %d, i: %d, top_c: %d\n", stack->b_small, i, top_c);
	// ft_printf("error\nabig: %d, i: %d, top_c: %d\n", stack->a_big, i, top_c);
	// ft_printf("error\nbbig: %d, i: %d, top_c: %d\n", stack->b_big, i, top_c);
	if (top_c != i && checks_order(stack, i, c_char, TRUE) == ERROR)
		return (error_start_nbr(stack, i, 'e'));
	++i;
	//ft_printf("after first error check passed\n");
	if (c_char == 'b')
		++i;
	while (i < stack->bottom)
	{
		if (checks_order(stack, i, c_char, FALSE) == ERROR)
			return (error_start_nbr(stack, i, 'e'));
		++i;
	}
	//ft_printf("after second error check passed\n");
	if ((c[top_c] != stack->a_small && c_char == 'a') || (c[top_c] != stack->b_big && c_char == 'b'))
	{
		i = top_c + 1;
		//ft_printf("c[i]: %d\n", c[i]);
		while ((c[i] != stack->a_small && c_char == 'a') || \
		(c[i] != stack->b_big && c_char == 'b'))
		{
			if (checks_order(stack, i, c_char, FALSE) == ERROR)
				return (error_start_nbr(stack, i, 'e'));
			++i;
		}
	}
	//ft_printf("shouldn't return error\n");
	return (error_start_nbr(stack, i, 't'));
}

/*
static void	stage_three_sort_b(t_stack *stack)
{
	if (stack->b_empty == FALSE && check_if_ordered(stack, stack->b, stack->top_b, 'b') == ERROR && stack->b_big != stack->b_small)
	{
		stack_rotate_init(stack, stack->b, stack->b_small, 'b');
	}
	else if (stack->b_empty == FALSE)
	{
		push_and_update(stack, 'a');
		*//*()
		if (stack->a[stack->bottom - 1] > stack->b[stack->top_b] && stack->a[stack->bottom - 2] < stack->b[stack->top_b])
		{
			rotate_stacks(stack, 'd', 'a');
			while (stack->a[stack->top_a] > stack->b[stack->top_b] && stack->a[stack->bottom - 1] < stack->b[stack->top_b])
				push_and_update(stack, 'a');
		}
		else if (stack->b[stack->top_b] > stack->a[stack->top_a] && stack->b[stack->top_b] < stack->a[stack->top_a + 1])
		{
			rotate_stacks(stack, 'r', 'a');
			while (stack->a[stack->top_a] > stack->b[stack->top_b] && stack->a[stack->bottom - 1] < stack->b[stack->top_b])
				push_and_update(stack, 'a');
			rotate_stacks(stack, 'd', 'a');
		}
		else if (stack->b[stack->top_b] > stack->a[stack->bottom - 1])
		{
			push_and_update(stack, 'a');
			rotate_stacks(stack, 'r', 'a');
		}
		else if (stack->b[stack->top_b] < stack->a[stack->top_a])
		{
			//make a check for if stack b is at either b_big or b_bigB
			// if not loop to nearest
			push_and_update(stack, 'a');
		}*/
	/*}
	else
	{
		ft_putstr("error");
		exit(1);
	}

}
*/

// still takes to many moves. move stuff to left side in chunks like other people has said?
// make sure sorting works. now sorting to b side works but still trouble getting it to the left

static void	already_sorted(t_stack *stack)
{
	int	i;
	int	index;
	int	nbr;
	int	len;
	int	small;

	i = 0;
	len = 0;
	small = stack->a_small;
	while (i < stack->bottom)
	{
		stack->a_small = stack->a[i];
		check_if_ordered(stack, stack->a, i, 'a');
		if (stack->start_nbr - i >= 3)
		{
			len = stack->start_nbr - i;
			index = i;
			nbr = stack->a[index];
			i = stack->start_nbr - 1;
			//ft_printf("len: %d	, index: %d	, nbr: %d, end nbr: %d\n", len, index, nbr, stack->a[stack->start_nbr - 1]);
		}
		++i;
	}
	stack->start_nbr = nbr;
	stack->a_small = small;
	//ft_printf("len: %d	, index: %d	", len, index);
}


// find the biggest sequence of already ordered numbers. push them to stack b
// locate next sorted sequence.
// sort as you make your way there
// as you find the next biggest sequence merge it with stack b
// only when last bit has been sorted will we push from stack b to a and merge the last bit


/*

ARG="-46 -5 -47 5 6 42 -35 35 -25 -31 43 36 44 21 -33 29 -13 45 -11 -10 22 50 -17 1 25 -3 -8 17 -44 -38 -22 31 -6 0 7 3 48 -20 -37 8 32 -28 15 41 19 -30 13 27 23 28 47 10 37 4 2 24 49 -18 12 -49 20 -40 14 -2 -4 -1 38 -16 16 -50 -32 -14 -7 -21 -29 18 -43 -9 11 -36 46 -15 -34 -24 -26 -27 40 -39 26 30 -19 9 -42 -48 39 -12 -45 33 34 -41 -23"; ./push_swap $ARG

*/

void	sort_stack(t_stack *stack)
{
	int	stage;
	int	b_ordered;

	//int i = 0;
	stage = 1;
	b_ordered = FALSE;
	already_sorted(stack);
	//ft_printf("nbr: %d, \n", stack->start_nbr);
	//exit(0);
	//int j = 0;
	//int stop = 0;
	// if i have one order stack a and b is empty or needs to be merged call the rotate function... or have it be stage 4... rotating...
	while (check_if_solved(stack, 'c') == ERROR)//i++ < 10 && 
	{
		// ft_putstr("\n");
		// ft_putnbr(stack->a[stack->bottom - 4]);
		// ft_putnbr(stack->a[stack->bottom - 3]);
		// ft_putnbr(stack->a[stack->bottom - 2]);
		// ft_putnbr(stack->a[stack->bottom - 1]);
		stack->a_ordered = check_if_ordered(stack, stack->a, stack->top_a, 'a');
		if (stack->b_small < stack->b_big)
			b_ordered = check_if_ordered(stack, stack->b, stack->top_b, 'b');
		if (stack->a_ordered == TRUE && (b_ordered == TRUE || stack->b_empty == TRUE))
		{
			if (stack->b_empty == TRUE)
				stage = 5;
			else
				stage = 4;
		}
		else if (stack->a_ordered == TRUE)
		{
			//if (stack->b_empty == FALSE)
			//	stage = 3;
			//else
			if (stack->b_empty == TRUE)
				stage = 5;
			else
				stage = 4;
		}
		//else if (stage == 1 && stack->median > (((stack->bottom - stack->top_a) / 2) + ((stack->bottom - stack->top_a) % 2)))
		//	++stage;
		if (stage == 1)
		{
			// int k = 0;
			// while (k < stack->bottom)
			// {
			// 	ft_printf("a[%d]: %d	b[%d]: %d\n", k, stack->a[k], k, stack->b[k]);
			// 	k++;
			// }
			//ft_putstr("stage1\n");
			//ft_printf("stack->a_ordered 1 = true: %d\n", stack->a_ordered);
			if ((stack->a[stack->bottom - 1] == stack->ordered_big || stack->bottom - stack->top_b > 10) && b_ordered == TRUE)
			{
				stack_rotate_init(stack, stack->b, stack->b_small, 'b');
				int i = 0;
			while (i < stack->bottom)
			{
				ft_printf("beforestack->ordered_big: %d, beforea[%d]: %d	b[%d]: %d\n", stack->ordered_big, i, stack->a[i], i, stack->b[i]);
				i++;
			
			}
				while (stack->b_empty == FALSE)
					push_and_update(stack, 'a');
				i = 0;
			while (i < stack->bottom)
			{
				ft_printf("afterstack->ordered_big: %d, beforea[%d]: %d	b[%d]: %d\n", stack->ordered_big, i, stack->a[i], i, stack->b[i]);
				i++;
			
			}
				int nbr = 0;
				int index = stack->top_a;
				if (stack->a[index] == stack->ordered_big)// && i + 1 != stack->bottom && stack->a_ordered == TRUE)
					nbr = stack->a[index + 1];
				else
				{
					while (index < stack->bottom)
					{
						if (stack->a[index] == stack->ordered_small)
						{
							if (index == stack->top_a)
								nbr = stack->a[stack->bottom - 1];
							else
								nbr = stack->a[index + 1];
							break ;
						}
						++index;
					}
				}
				//ft_printf("nbr: %d\n", nbr);
				stack->first_small = FALSE;
				ft_printf("nbr: %d\n", nbr);
				if (nbr == 50)
					exit(0);
				stack_rotate_init(stack, stack->a, nbr, 'a');
				
			}
			else
			{
				if (stack->ordered_small > stack->ordered_big)
				{
					push_and_update(stack, 'b');
					if (stack->a[stack->top_a] > stack->a[stack->top_a + 1])
						switch_stacks(stack, 'a');
				}
				else
				{
					solve_and_print(stack, "rra");
					//if (stack->ordered_small > stack->ordered_big && stack->a[stack->top_a + 1] == stack->ordered_small && stack->a[stack->top_a] < stack->ordered_small)
					//{
					//	stack->ordered_small = stack->a[stack->top_a];
					//}
					push_and_update(stack, 'b');
				}
			}
			
			// int i = 0;
			// while (i < stack->bottom)
			// {
			// 	ft_printf("a[%d]: %d	b[%d]: %d\n", i, stack->a[i], i, stack->b[i]);
			// 	i++;
			
			// }
				
			//stage_one_split(stack);
	// 		ft_putstr("\n");
	// ft_putnbr(stack->a[stack->bottom - 4]);
	// ft_putnbr(stack->a[stack->bottom - 3]);
	// ft_putnbr(stack->a[stack->bottom - 2]);
	// ft_putnbr(stack->a[stack->bottom - 1]);
	// 	ft_putstr("\n");
	// ft_putnbr(stack->b[stack->bottom - 4]);
	// ft_putnbr(stack->b[stack->bottom - 3]);
	// ft_putnbr(stack->b[stack->bottom - 2]);
	// ft_putnbr(stack->b[stack->bottom - 1]);
		}
		else if (stage == 4)
		{
			ft_putstr("stage4\n");


/*

stuck on stage 4 - there is a continuous running loop that i need to find

it stops pushign to stage a at some point

ARG="-12 -17 10 24 -47 31 7 -21 -48 -40 -30 -22 38 30 -33 48 -36 -2 11 -43 14 -41 42 5 -9 -42 3 21 46 -32 -1 -45 -8 23 29 -35 36 -46 9 -25 -16 33 -24 43 -44 27 -14 49 -34 -18 -7 41 45 13 50 8 19 32 4 -31 -3 -10 34 -19 -6 -27 25 -39 -28 -49 47 37 28 -23 39 -26 6 -37 -11 1 15 -50 -5 44 -20 35 22 20 16 -13 -15 18 12 0 -29 -38 -4 2 40 26 17"; ./push_swap $ARG


*/


			// is it important to rotate stack a? maybe yes
			//stack_rotate_init(stack, stack->a, stack->a_big, 'a');
			// int k = 0;
			// while (k < stack->bottom)
			// {
			// 	ft_printf("a[%d]: %d	b[%d]: %d\n", k, stack->a[k], k, stack->b[k]);
			// 	k++;
			// }
			// exit(0);
			if (stack->b_empty == FALSE)
			{
				stack_rotate_init(stack, stack->b, stack->b_small, 'b');
				while (stack->b_empty == FALSE)
				{
		//			ft_printf("%d\n", stack->b_empty);
					push_and_update(stack, 'a');
		// 				ft_printf("%d\n", stack->b_empty);
		// 			int i = 0;
		// while (i < stack->bottom)
		// {
		// 	ft_printf("a[%d]: %d	b[%d]: %d\n", i, stack->a[i], i, stack->b[i]);
		// 	i++;

		// }
		// j++;
		// 	if (j > 42)
		// 		exit(0);
		}	}
			if (stack->b_empty == TRUE)
			{
				stack_rotate_init(stack, stack->a, stack->a_big, 'a');
			}

	// ft_putstr("\n");
	// ft_putnbr(stack->b[stack->bottom - 4]);
	// ft_putnbr(stack->b[stack->bottom - 3]);
	// ft_putnbr(stack->b[stack->bottom - 2]);
	// ft_putnbr(stack->b[stack->bottom - 1]);
	// ft_printf("\nbig: %d, small: %d\nstack->a", stack->b_big, stack->b_small);
	// ft_putchar('\n');
	// ft_putnbr(stack->a[0]);
	// ft_putnbr(stack->a[1]);
	// ft_putnbr(stack->a[2]);
	// ft_putnbr(stack->a[3]);
	// ft_putnbr(stack->a[4]);
	// ft_putnbr(stack->a[5]);
		//	if (stack->b_empty == TRUE)
		//	{
				/*
				int i = 0;
				while (i < stack->bottom)
				{
					ft_printf("a[%d]: %d	b[%d]: %d\n", i, stack->a[i], i, stack->b[i]);
					i++;
				}*/
			//	exit(0);
			//}
			//++j;
			//if (j > 10)
			//	exit(0);
			
			
		}
		else if (stage == 5)
		{
			//ft_putstr("stage5\n");
			//exit(0);
			stack_rotate_init(stack, stack->a, stack->a_big, 'a');
		}
		else if (stage == 3)
		{
		/*	ft_putstr("stage3\n"); SHOULD THIS STAGE BE DELETED???
		//	exit(0);
			stage_three_sort_b(stack);
		  ft_putnbr(stack->a[stack->bottom - 6]);
			ft_putnbr(stack->a[stack->bottom - 5]);
		  ft_putnbr(stack->a[stack->bottom - 4]);
		  ft_putnbr(stack->a[stack->bottom - 3]);
		  ft_putnbr(stack->a[stack->bottom - 2]);
		  ft_putnbr(stack->a[stack->bottom - 1]);
			//exit(0);*/
		}
		/*int i = 0;
		while (i < stack->bottom)
		{
			ft_printf("a[%d]: %d	b[%d]: %d\n", i, stack->a[i], i, stack->b[i]);
			i++;
		
		}*/
	}

	/*ft_putnbr(stack->a[0]);
	ft_putnbr(stack->a[1]);
	ft_putnbr(stack->a[2]);
	ft_putnbr(stack->a[3]);
	ft_putnbr(stack->a[4]);*/
}

/*

rust is a good language to learn

i = 1;
	j = 0;
	int nbr;
	nbr = argc / 2;
	if (argc % 2 > 0)
		nbr += 1;
	 need to use this number to create malloc for stack b

stack sorting logic

collect middle number aka argc / 2

while loop

1. check if stack a is sorted
	if sorted check if b is empty
2. check if stack b is sorted
3. check first two elements of stack a
	if below middle number(try with 1/4) or equal to then move to stack b if following conditions are meet
		the next number in the stack isn't the closest above number with the one we are comparing to
		(ex if we look at 2 but the one below it is 3 then it is sorted correctly - so dont move to stack b if a is sorted or maybe more check if there is one difference)
4. switch top if wrong order (do with both stacks)
5. rotate one way depending on where the next closest to middle number is (check is stack b also should rotate)
6. 

*/




/*

	identify the lowest number location and try to get that to the bottom
	in the process of that move stuff in right order and move stuff to stack b
	weather the computer chooses to use rra or ra depends on which way is closest for it to get there in least amount of moves
	on the way the computer will check if any number is not in right order and will switch their position
	depending on which way we rotate the way we will switch will also change

	when lowest number is at the bottom 

	ex if putting top element in the bottom
		if (stack->a[top_a] < stack->a[top_a + 1])
			if (stack->b_empty == FALSE && stack->a[stack->top_a] < stack->b[stack->top_b])
				//maybe check how to quickliest get it to the right position
				if (stack->a[top_a] > stack->b[top_b])
					if (stack->b[stack->top_b + 1] > stack->b[stack->bottom - 1])
						sb swap top of stack b
					//make some kind of looping either back and forward and have it loop back after pushing it to correct position
					//rr or rb thingy
					push to b
					// when moving it back we need to check if moving same direction would make sense for stack a
					//ex if stack->a[top_a] > stack->b[top_b + 1] && stack->a[top_a + 1] < stack->b[top_b + 1]
					// if this happens the next move HAS TO BE 'pa'
					// only can do this if bottom is lowest number and i have to make sure it is assembled in reverse order so i can push it to top of stack b

			if (stack->a[stack->top_a + 1] > stack->a[stack->bottom - 1])
				switch(maybe also here with b_stack if possible)
		if (stack->a[top_a] > stack->a[stack->bottom - 1])
			if (stack->b_empty == FALSE && stack->b[top_b] < stack->b[stack->bottom - 1])
				reverse to bottom rr
			else
				reverse to bottom ra
		else
			push to b
				//make sure b is in order and if moves make sense to do on both stacks it will be done here
		to know weather to put current number to the bottom you check if the top number is bigger than the bottom number
		
		when biggest number is at bottom
		if (stack->a[top_a] < stack->a[top_a + 1])

	if putting bottom to top
		if (nbr < nbr + 1)
			switch
		else
			keep position

	when stack a bottom is correct slowly move stuff to stack b until stack is down to two ordered stacks
	depending on which is longer we will do either rra or ra we rotate until the bottom ordered stack is on top and we will move stuff from stack b
	if the other sorted stack isn't the end we will move when stack->b top is smaller than the stack-a[bottom];


when two sorted stacks in stack a and one sorted stack b i will merge them together

check at what point in the array of stack->a is sorted correctly

ALWAYS keep stack b in order as much as possible

	5
	3
	6
	4
	2
	0
	1

//rotate logic	
	ra
	pb
	ra
	pb
	pb
	rr
	ra
	pa
	pa
	pa
	rra
	rra






./checker 0 4 7 -9 9 2 10 -4 5 3 1 8 -6 6
pb
pb
ra
pb
rr
pb
sb
ra
rrb
pb
rb
rr
pb
sb
rra
pb
rrb
rrb
rrb
pb
sa
rb
rb
rb
pb
rb
rr
pb
pb
rra
pa
pa
pa
pa
pa
pa
pa
pa
pa
pa
pa

41




moving it downwards instead of up rra
pb
pb
rra
rra
pb
rb
pb
pb
pb
rr
sa
rr
rb
rb
pb
rb
rb
pb
sa
rrb
rrb
pb
sa
pb
rrb
pb
rrb
rrb
pa
pa
pa
pa
sb
pa
sb
pa
pa
pa
pa
pa
pa


41


top two and bottom system
pb
rra
sa
rra
pb
pb
rrb
sb
pb
sa
pb
rra
sa
rra
rb
pa
rra
pb
rra
rra
ss
pb
sb
pa
pa
rra
pb
rra
rra
ss
ra
pa
sb
pa
pa
pa
pa

37

keep track of top and bottom in each stack so i then can know if they have been divided with all the numbers


./checker 5 4 3 2 1
ra
sa
pb
sa
pb
ss
ra
pa
pa
rra

10

keep middle 3 everything else goes to stack b

pb
pb
ra
ss
pa
pa
ra
ra

8

jefs version

sa
ra
pb
ra
pb
ra
pa
pa

8

./checker 9 8 7 6 5 4 3
sa
rra
pb
rra
pb
rra
pb
rra
pb
rra
pa
pa
pa
pa

14

ra
sa
pb
sa
pb
ss
pb
sa
rb
pb
rb
sa
pb
rb
pa
pa
pa
pa
pa

19



sort only top two and bottom
sa
rra
rra
sa
pb
rra
sa
pb
rra
sa
pb
rra
sa
pa
pa
pa

16


./checker 8 4 9 3 6 5 7
sa
rra
sa
rra
sa
pa
rra
sa
rra
pa
sa

11



two top and bottom compare method
./checker -5 8 -6 9 -9 10 2 3 1 4 0 -4 5 -8
rra
pb
pb
rra
rra
pb
rra
pb
rra
rra
pb
rra
rra
rra
pb
rra
pb
rb
rra
rra
sa
ra
pa
ra
ra
pa
pa
pa
pa
rra
pa
pa

32


jeffs method
./checker -5 8 -6 9 -9 10 2 3 1 4 0 -4 5 -8
pb
rra
pb
rrr
pb
rra
pb
sb
rra
pb
sb
rra
pb
sb
rra
rb
rb
pb
rrr
pb
sb
rra
rb
pb
sb
rrr
sa
rrr
pb
rra
sa
rb
pa
pa
pa
pa
pa
pa
pa
pa
rra
pa
pa

42





sort only top two and bottom
keep track of lowest and heighest number in each stack
stack->a_low
stack->a_heigh
stack->b_low
stack->b_heigh
stack->b_lowB
stack->b_heighB


pseudo code

stack->a_low = lowest_number
stack->a_heigh = heighest_number
stack->b_low = 1;
stack->b_heigh = -1;
stack->b_lowBig = 1;
stack->b_heighBig = -1;

stage = 1;
while (hasn't been solved)
{
	if (stack a get's solved and stack b is not empty)
		stage++;
	if (stage == 1)
	{
		if (stack->a[bottom - 2] == a_low && stack->a[bottom - 1] == stack->a_heigh)
			rra
			rra
			sa
			ra
		else if (stack->a[top_a] < stack->b_low)
			push to stack b
			rb
		else if (stack->a[top_a] > stack->a[top_a + 1])
		{
			if (same can be done for stack b)
				switch position ss
			else
				switch position sa
		}
		else if (stack->a[bottom - 1] > stack->a[top_a] && stack->a[bottom - 1] > stack->a[top_a + 1])
		{
			
			if (stack->a[bottom - 1] > stack->a[top_a + 3])
			{
				if (same can be done for stack b)
					rrr
				else
					rra
				push top elements to stack b
					if stack->b[top_a] != stack->b_heigh
						rrb or rb
				update
					stack->b_lowBig && b_heighBig
			}
			else
			{
				push two top elements to stack b
					if stack->b[top_a] != stack->b_heigh
						rrb or rb
				if (same can be done for stack b)
					rrr
				else
					rra
				update
					stack->b_low && b_heigh (only if heighter than what was previous heighest and lowest)
			}
		}
		else if (stack->a[bottom - 1] > stack->a[top_a] && tack->a[bottom - 1] < stack->a[top_a + 1])
		{
			push first element to stack b
				make sure in right order or else need to rotate before pushing
			if (same can be done for stack b)
				rrr
			else
				rra
			
		}
		else if (stack->a[bottom - 1] < stack->a[top_a])
		{
			if (same can be done for stack b)
				rrr
			else
				rra
		}
	}
	else if (stage == 2)
	{
		if (stack->b[top_b] == stack->b_heighBig)
		{
			pa
			update what is the new b_heighBig and b_lowBig
			update stack->a_low and a_heigh
			ra
		}
		else if (stack->b[top_b] == stack->b_heigh)
		{
			while (stack->a[top_a] < stack->b[top_b])
			{
				ra
			}
			while (stack->a[top_a] > stack->b[top_b] && stack->a[bottom - 1] < stack->b[top_b])
				pa
				update what is the new b_heighBig and b_lowBig
				update stack->a_low and a_heigh
			if (stack->a[bottom - 1] < stack->a[top_a])
				rra
		}

	}
}



*/
