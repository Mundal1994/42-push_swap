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

static void	old_sorting_algo(t_stack *stack)
{
	int	stage;
	int	b_ordered;

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
				// I THINK THIS CALCULATION THINGY IS WRONG !
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
				//ft_printf("nbr: %d\n", nbr);
				//if (nbr == 50)
				//	exit(0);
				ft_printf("stack->ordered_big: %d\n", stack->ordered_big);
				stack_rotate_init(stack, stack->a, 50, 'a');
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
					push_and_update(stack, 'b');
				}
			}
		}
		else if (stage == 4)
		{
			ft_putstr("stage4\n");

/*

stuck on stage 4 - there is a continuous running loop that i need to find

it stops pushign to stage a at some point

ARG="-12 -17 10 24 -47 31 7 -21 -48 -40 -30 -22 38 30 -33 48 -36 -2 11 -43 14 -41 42 5 -9 -42 3 21 46 -32 -1 -45 -8 23 29 -35 36 -46 9 -25 -16 33 -24 43 -44 27 -14 49 -34 -18 -7 41 45 13 50 8 19 32 4 -31 -3 -10 34 -19 -6 -27 25 -39 -28 -49 47 37 28 -23 39 -26 6 -37 -11 1 15 -50 -5 44 -20 35 22 20 16 -13 -15 18 12 0 -29 -38 -4 2 40 26 17"; ./push_swap $ARG


*/

			if (stack->b_empty == FALSE)
			{
				stack_rotate_init(stack, stack->b, stack->b_small, 'b');
				while (stack->b_empty == FALSE)
					push_and_update(stack, 'a');}
			if (stack->b_empty == TRUE)
			{
				stack_rotate_init(stack, stack->a, stack->a_big, 'a');
			}
		}
		else if (stage == 5)
		{
			//ft_putstr("stage5\n");
			//exit(0);
			stack_rotate_init(stack, stack->a, stack->a_big, 'a');
		}
	}
}

static int	islist(t_stack *stack, int nbr)
{
	int	i;

	i = 0;
	while (i < stack->len)
	{
		if (nbr == stack->list[i])
			return (i);
		++i;
	}
	return (-1);
}

void	sort_stack(t_stack *stack, int longest_list)
{
	int	stage;
	int	b_ordered;

	//int i = 0;
	stage = 1;
	b_ordered = FALSE;
	already_sorted(stack);
	int i = 0;
	while (i < stack->len)
	{
		ft_printf("stack->list[%d]: %d\n", i, stack->list[i]);
		++i;
	}
	if (longest_list == 0)
		old_sorting_algo(stack);
	else
	{
		while (check_if_solved(stack, 'c') == ERROR)
		{
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
				if (stack->b_empty == TRUE)
					stage = 5;
				else
					stage = 4;
			}
			if (stage == 1)
			{
				/*if ((stack->a[stack->bottom - 1] == stack->ordered_big || stack->bottom - stack->top_b > 10) && b_ordered == TRUE)
				{
					stack_rotate_init(stack, stack->b, stack->b_small, 'b');
					while (stack->b_empty == FALSE)
						push_and_update(stack, 'a');
					stack->first_small = FALSE;
					stack_rotate_init(stack, stack->a, stack->ordered_big, 'a');
				}
				else
				{*/
					// if (stack->ordered_small > stack->ordered_big)
					// {
					// 	push_and_update(stack, 'b');
					// 	if (stack->a[stack->top_a] > stack->a[stack->top_a + 1])
					// 		switch_stacks(stack, 'a');
					// }
					// else
					// {
						int index = islist(stack, stack->a[stack->top_a]);
						if (index > -1)
							solve_and_print(stack, "rra");
						else
							push_and_update(stack, 'b');
						ft_printf("index: %d\n", index);
					//}
				//}
			}
			else if (stage == 4)
			{
				ft_putstr("stage4\n");

	/*

	stuck on stage 4 - there is a continuous running loop that i need to find

	it stops pushign to stage a at some point

	ARG="-12 -17 10 24 -47 31 7 -21 -48 -40 -30 -22 38 30 -33 48 -36 -2 11 -43 14 -41 42 5 -9 -42 3 21 46 -32 -1 -45 -8 23 29 -35 36 -46 9 -25 -16 33 -24 43 -44 27 -14 49 -34 -18 -7 41 45 13 50 8 19 32 4 -31 -3 -10 34 -19 -6 -27 25 -39 -28 -49 47 37 28 -23 39 -26 6 -37 -11 1 15 -50 -5 44 -20 35 22 20 16 -13 -15 18 12 0 -29 -38 -4 2 40 26 17"; ./push_swap $ARG


	*/
				if (stack->b_empty == FALSE)
				{
					stack_rotate_init(stack, stack->b, stack->b_small, 'b');
					while (stack->b_empty == FALSE)
						push_and_update(stack, 'a');
				}
				if (stack->b_empty == TRUE)
				{
					stack_rotate_init(stack, stack->a, stack->a_big, 'a');
				}
			}
			else if (stage == 5)
			{
				//ft_putstr("stage5\n");
				stack_rotate_init(stack, stack->a, stack->a_big, 'a');
			}
		}
	}
}

/*

rust is a good language to learn

*/
