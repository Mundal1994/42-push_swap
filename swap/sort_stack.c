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
	//ft_printf("error\nbbig: %d, i: %d, top_c: %d\n", stack->b_big, i, top_c);
	if (top_c != i && checks_order(stack, i, c_char, TRUE) == ERROR)
		return (error_start_nbr(stack, i, 'e'));
	++i;
	if (c_char == 'b')
		++i;
	//ft_printf("hello1\n");
	while (i < stack->bottom)
	{
		if (checks_order(stack, i, c_char, FALSE) == ERROR)
			return (error_start_nbr(stack, i, 'e'));
		++i;
	}
	//ft_printf("second error check passed\n");
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
	return (error_start_nbr(stack, i, 't'));
}

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
/*
static void	isolate_sorted_list(t_stack *stack, int *c, int top_c, char c_char)
{
	int index = islist(stack, c[top_c]);
	if (index > -1 && c_char == 'a')
	{
		while (c[top_c] > c[top_c + 1] && c[top_c + 1] > c[stack->bottom - 1])
		{
			switch_stacks(stack, 'a');
			solve_and_print(stack, "ra");
		}
		solve_and_print(stack, "ra");
	}
	else if (index > -1 && c_char == 'b' && !(c[top_c] < stack->a[stack->top_a] && c[top_c] > stack->a[stack->bottom - 1]))
	{
		while (c[top_c] < c[top_c + 1] && c[top_c + 1] < c[stack->bottom - 1])
		{
			switch_stacks(stack, 'b');
			push_and_update(stack, 'a');
			//solve_and_print(stack, "rb");
		}
		//solve_and_print(stack, "rb");
		push_and_update(stack, 'a');
	}
	else if (c_char == 'a')
	{
		if (c[top_c] < stack->a[stack->bottom - 1] && (c[top_c] > stack->a[stack->bottom - 2] || islist(stack, c[stack->bottom - 1]) == 0))
		{
			solve_and_print(stack, "rra");
			switch_stacks(stack, 'a');
			solve_and_print(stack, "ra");
			solve_and_print(stack, "ra");
		}
		else
			push_and_update(stack, 'b');
	}
	else if (c_char == 'b')
	{
		if (c[top_c] < c[top_c + 1])
		{
			if (c[top_c] < c[stack->bottom - 1] + 20)
				solve_and_print(stack, "rb");
			else
				switch_stacks(stack, 'b');
		}
		// else if (c[top_c] < stack->a[stack->top_a] && c[top_c] > stack->a[stack->bottom - 1])
		// {
		// 	while (c[top_c] < stack->a[stack->top_a] && c[top_c] > stack->a[stack->bottom - 1])
		// 		push_and_update(stack, 'a');
		// }
		// else if (c[top_c] > stack->a_big - ((stack->bottom / 100) * 80))
		// 	push_and_update(stack, 'a');
		else if (c[top_c] > c[stack->bottom - 1] && islist(stack, c[stack->bottom - 1]) < 0)
		{
			solve_and_print(stack, "rrb");
			switch_stacks(stack, 'b');
			solve_and_print(stack, "rb");
			solve_and_print(stack, "rb");
		}
		else
		{
			solve_and_print(stack, "rb");
			//push_and_update(stack, 'a');
		}

		//push_and_update(stack, 'a');
	}
}*/

static int	is_split(t_stack *stack)
{
	int i = stack->top_a;

	while (i < stack->bottom)
	{
		if (stack->a[i] <= stack->small_heigh || stack->a[i] >= stack->big_low)
			return (FALSE);
		++i;
	}
	return (TRUE);
}
/*
static void	rotate_stack(t_stack *stack, char c, char d)
{
	if (c == 'a')
	{
		if (d == 'd')
			solve_and_print(stack, "rra");
		else
			solve_and_print(stack, "ra");
	}
	else
	{
		if (d == 'd')
			solve_and_print(stack, "rrb");
		else
			solve_and_print(stack, "rb");
	}
}
*/

static int	index_of_nbr(t_stack *stack, int start, int value, int d)
{
	int	i;

	i = start;
	if (d == 'd')
	{
		while (i > stack->top_b)
		{
			if (stack->b[i] <= value)
				return (i);
			--i;
		}
	}
	else
	{
		while (i < stack->bottom)
		{
			if (stack->b[i] > value)
				return (i);
			++i;
		}
	}
	return (-1);
}

static int	index_of_nbr2(t_stack *stack, int start, int value, int d)
{
	int	i;

	i = start;
	if (d == 'd')
	{
		while (i > stack->top_b)
		{
			if (stack->b[i] <= value)
				return (i);
			--i;
		}
	}
	else
	{
		while (i < stack->bottom)
		{
			if (stack->b[i] <= value)
				return (i);
			++i;
		}
	}
	return (-1);
}

static void	sort_numbers_mid(t_stack *stack, int calc, int multi)
{
	int d;
	int first = TRUE;
	--multi;
	int mid_calc = stack->mid_heigh - (calc * multi);
	--multi;
	while (multi >= -1)
	{
		if (first == TRUE && stack->b[stack->top_b] <= mid_calc)
			push_and_update(stack, 'a');
		else if (first == TRUE)
		{
			d = calc_push_a_rotation(stack, stack->b[index_of_nbr2(stack, stack->top_b + 1, mid_calc, 'r')], stack->top_a);
			if (d == FALSE)
				solve_and_print(stack, "rr");
			else
				solve_and_print(stack, "rb");
		}
		else if (first == FALSE && stack->b[stack->top_b] <= mid_calc && stack->b[stack->top_b] > stack->small_heigh && stack->b[stack->top_b] < stack->big_low)
		{
			push_and_update(stack, 'a');
		}
		else if (first == FALSE)
		{
			d = calc_push_a_rotation(stack, stack->b[index_of_nbr2(stack, stack->bottom - 1, mid_calc, 'd')], stack->top_a);
			if (d == TRUE)
				solve_and_print(stack, "rrr");
			else
				solve_and_print(stack, "rrb");
		}
		if (first == FALSE && stack->b[stack->bottom - 1] <= stack->small_heigh)
		{
			mid_calc = stack->mid_heigh - (calc * multi);
			--multi;
			first = TRUE;
		}
		else if (first == TRUE && stack->b[stack->top_b] >= stack->big_low)
		{
			first = FALSE;
			mid_calc = stack->mid_heigh - (calc * multi);
			--multi;
			d = calc_push_a_rotation(stack, stack->b[index_of_nbr2(stack, stack->bottom - 1, mid_calc, 'd')], stack->top_a);
			if (d == TRUE)
				solve_and_print(stack, "rrr");
			else
				solve_and_print(stack, "rrb");
		}
	}
}

/*	apply same rotation logic to middle and small numbers	*/

static void	sort_numbers_big(t_stack *stack, int calc, int multi)
{
	int	first = TRUE;
	int	d;
	--multi;
	int big_calc = stack->big_heigh - (calc * multi);
	--multi;
	while (multi >= -1)
	{
		if (first == TRUE && stack->b[stack->top_b] <= big_calc)
		{
			push_and_update(stack, 'a');
		}
		else if (first == TRUE)
		{
			d = calc_push_a_rotation(stack, stack->b[index_of_nbr2(stack, stack->top_b + 1, big_calc, 'r')], stack->top_a);
			if (d == FALSE)
				solve_and_print(stack, "rr");
			else
				solve_and_print(stack, "rb");
		}
		else if (first == FALSE && stack->b[stack->top_b] <= big_calc && stack->b[stack->top_b] >= stack->big_low)
		{
			push_and_update(stack, 'a');
		}
		else if (first == FALSE)
		{
			d = calc_push_a_rotation(stack, stack->b[index_of_nbr2(stack, stack->bottom - 1, big_calc, 'd')], stack->top_a);
			if (d == TRUE)
				solve_and_print(stack, "rrr");
			else
				solve_and_print(stack, "rrb");
		}
		if (first == FALSE && stack->b[stack->bottom - 1] <= stack->small_heigh)
		{
			big_calc = stack->big_heigh - (calc * multi);
			--multi;
			first = TRUE;
		}
		else if (first == TRUE && stack->b[stack->top_b] <= stack->small_heigh)
		{
			first = FALSE;
			big_calc = stack->big_heigh - (calc * multi);
			--multi;
			d = calc_push_a_rotation(stack, stack->b[index_of_nbr2(stack, stack->bottom - 1, big_calc, 'd')], stack->top_a);
			if (d == TRUE)
				solve_and_print(stack, "rrr");
			else
				solve_and_print(stack, "rrb");
		}
	}
}
/*
static void	sort_small_nbr(t_stack *stack, int calc)
{
	int first = TRUE;
	int third = FALSE;
	int	first_nbr = 0;
	int small_calc = stack->small_heigh - (calc * 2);
	int d;
	first_nbr = stack->small_low;
	while (stack->b_empty == FALSE)
	{
		if (stack->b[stack->top_b] >= small_calc)
			push_and_update(stack, 'a');
		// else if (first == FALSE && stack->b[stack->top_b] > small_calc)
		// {
		// 	push_and_update(stack, 'a');
		// }
		else
		{
			d = calc_push_a_rotation(stack, stack->b[index_of_nbr(stack, stack->top_b + 1, small_calc, 'r')], stack->top_a);
			if (d == FALSE)
				solve_and_print(stack, "rr");
			else
				solve_and_print(stack, "rb");
			// int l = 0;
			// while (l < stack->bottom)
			// {
			// 	ft_printf("stack->a[%d]: %d, stack->b[%d]: %d\n", l, stack->a[l], l, stack->b[l]);
			// 	l++;
			// }
			// ft_printf("first: %d, first_nbr: %d\n", first, first_nbr);
			// ft_printf("stack->small_heigh - ((stack->small_heigh - stack->small_low) / 2): %d\n", stack->small_heigh - ((stack->small_heigh - stack->small_low) / 2));
		}
		if (stack->b[stack->top_b] == first_nbr && first == FALSE)
		{
			third = TRUE;
			small_calc = stack->small_heigh;
		}
		else if (stack->b[stack->top_b] == first_nbr)
		{
			first = FALSE;
			small_calc = stack->small_heigh - (calc * 3);
		}
	}
	//ft_printf("finished small stack\n");
}*/

void	sort_stack(t_stack *stack)
{
	int	stage;
	int	b_ordered;

	stage = 1;
	b_ordered = FALSE;
	already_sorted(stack);
	if (check_if_solved(stack, 'c') == ERROR)
	{
		while (is_split(stack) == FALSE)
		{
			if (stack->a[stack->top_a] <= stack->small_heigh)
			{
				push_and_update(stack, 'b');
				if (stack->a[stack->top_a] > stack->small_heigh && stack->a[stack->top_a] < stack->big_low)
					solve_and_print(stack, "rr");
				else
					solve_and_print(stack, "rb");
			}
			else if (stack->a[stack->top_a] >= stack->big_low)
			{
				push_and_update(stack, 'b');
			}
			else
			{
				solve_and_print(stack, "ra");
			}
		}
		longest_list(stack, 'a');
		while (check_if_ordered(stack, stack->a, stack->top_a, 'a') != TRUE)
		{
			if (islist(stack, stack->a[stack->top_a]) < 0)
			{
				push_and_update(stack, 'b');
			}
			else
			{
				solve_and_print(stack, "ra");
			}
		}
		int first = TRUE;
		// int l = 0;
		// while (l < stack->bottom)
		// {
		// 	ft_printf("stack->a[%d]: %d, stack->b[%d]: %d\n", l, stack->a[l], l, stack->b[l]);
		// 	l++;
		// }
		///exit (0);
		/*int d;
		int mid_calc = stack->mid_heigh - ((stack->mid_heigh - stack->mid_low) / 2);
		while (stack->b[stack->top_b] < stack->big_low && stack->b[stack->top_b] > stack->small_heigh)
		{
			if (first == TRUE && stack->b[stack->top_b] > mid_calc)
				push_and_update(stack, 'a');
			else if (first == TRUE)
			{
				d = calc_push_a_rotation(stack, stack->b[index_of_nbr(stack, stack->top_b + 1, mid_calc, 'r')], stack->top_a);
				if (d == FALSE)
					solve_and_print(stack, "rr");
				else
					solve_and_print(stack, "rb");
			}
			else if (first == FALSE && stack->b[stack->top_b] <= mid_calc)
			{
				push_and_update(stack, 'a');
				if (stack->b[stack->bottom - 1] > stack->small_heigh)
				{
					d = calc_push_a_rotation(stack, stack->b[index_of_nbr(stack, stack->bottom - 1, mid_calc, 'd')], stack->top_a);
					if (d == TRUE)
						solve_and_print(stack, "rrr");
					else
						solve_and_print(stack, "rrb");
				}
			}
			if (first == TRUE && stack->b[stack->top_b] >= stack->big_low)
			{
				first = FALSE;
				d = calc_push_a_rotation(stack, stack->b[index_of_nbr(stack, stack->bottom - 1, mid_calc, 'd')], stack->top_a);
				if (d == TRUE)
					solve_and_print(stack, "rrr");
				else
					solve_and_print(stack, "rrb");
			}
		}*/
		int multi = 6;
		sort_numbers_mid(stack, (stack->mid_heigh - stack->mid_low) / multi, multi);



		// int l = 0;
		// while (l < stack->bottom)
		// {
		// 	ft_printf("stack->a[%d]: %d, stack->b[%d]: %d\n", l, stack->a[l], l, stack->b[l]);
		// 	l++;
		// }
		// exit (0);
		multi = 6;
		sort_numbers_big(stack, (stack->big_heigh - stack->big_low) / multi, multi);
		/*first = TRUE;
		int big_calc = stack->big_heigh - ((stack->big_heigh - stack->big_low) / 2);
		while (stack->b[stack->top_b] > stack->small_heigh && stack->b_empty == FALSE)
		{
			if (first == TRUE && stack->b[stack->top_b] <= big_calc)
				push_and_update(stack, 'a');
			else if (first == TRUE)
			{
				d = calc_push_a_rotation(stack, stack->b[index_of_nbr(stack, stack->top_b + 1, big_calc, 'r')], stack->top_a);
				if (d == FALSE)
					solve_and_print(stack, "rr");
				else
					solve_and_print(stack, "rb");
			}
			else if (first == FALSE && stack->b[stack->top_b] > big_calc)
			{
				push_and_update(stack, 'a');
				if (stack->b[stack->bottom - 1] <= stack->small_heigh)
				{
					d = calc_push_a_rotation(stack, stack->b[index_of_nbr(stack, stack->bottom - 1, big_calc, 'd')], stack->top_a);
					if (d == TRUE)
						solve_and_print(stack, "rrr");
					else
						solve_and_print(stack, "rrb");
				}
			}
			if (first == TRUE && stack->b[stack->top_b] <= stack->small_heigh)
			{
				first = FALSE;
				d = calc_push_a_rotation(stack, stack->b[index_of_nbr(stack, stack->bottom - 1, big_calc, 'd')], stack->top_a);
				if (d == TRUE)
					solve_and_print(stack, "rrr");
				else
					solve_and_print(stack, "rrb");
			}
			// int l = 0;
			// while (l < stack->bottom)
			// {
			// 	ft_printf("stack->a[%d]: %d, stack->b[%d]: %d\n", l, stack->a[l], l, stack->b[l]);
			// 	l++;
			// }
		}*/
		// int l = 0;
		// while (l < stack->bottom)
		// {
		// 	ft_printf("stack->a[%d]: %d, stack->b[%d]: %d\n", l, stack->a[l], l, stack->b[l]);
		// 	l++;
		// }
		// exit (0);
		int d;
		first = TRUE;
		int	first_nbr = 0;
		int small_calc = stack->small_heigh - ((stack->small_heigh - stack->small_low) / 2);
		while (stack->b_empty == FALSE)
		{
			if (first == TRUE && stack->b[stack->top_b] > small_calc)
				push_and_update(stack, 'a');
			else if (first == FALSE && stack->b[stack->top_b] <= small_calc)
			{
				push_and_update(stack, 'a');
			}
			else
			{
				if (!first_nbr)
					first_nbr = stack->b[stack->top_b];
				d = calc_push_a_rotation(stack, stack->b[index_of_nbr(stack, stack->top_b + 1, small_calc, 'r')], stack->top_a);
				if (d == FALSE)
					solve_and_print(stack, "rr");
				else
					solve_and_print(stack, "rb");
				// int l = 0;
				// while (l < stack->bottom)
				// {
				// 	ft_printf("stack->a[%d]: %d, stack->b[%d]: %d\n", l, stack->a[l], l, stack->b[l]);
				// 	l++;
				// }
				// ft_printf("first: %d, first_nbr: %d\n", first, first_nbr);
				// ft_printf("stack->small_heigh - ((stack->small_heigh - stack->small_low) / 2): %d\n", stack->small_heigh - ((stack->small_heigh - stack->small_low) / 2));
			}
			if (stack->b[stack->top_b] == first_nbr)
				first = FALSE;
		}
		//sort_small_nbr(stack, (stack->small_heigh - stack->small_low) / 2);
		stack_rotate_init(stack, stack->a, stack->a_big, 'a');
		// int l = 0;
		// while (l < stack->bottom)
		// {
		// 	ft_printf("stack->a[%d]: %d, stack->b[%d]: %d\n", l, stack->a[l], l, stack->b[l]);
		// 	l++;
		// }
		// exit(0);
		// int l = 0;
		// while (l < stack->bottom)
		// {
		// 	ft_printf("stack->a[%d]: %d, stack->b[%d]: %d\n", l, stack->a[l], l, stack->b[l]);
		// 	l++;
		// }
		// i = 0;
		// while (i < stack->len)
		// {
		// 	ft_printf("stack->list[%d]: %d\n", i, stack->list[i]);
		// 	++i;
		// }
	}
}



/*

look at how algorythm is working.

something wrong with pushing to stack a were it loops way to much.
maybe figure out a better way to sort stack b than pushing directly to stack a


is there a way to sort as many of the chunks as i'm pushing to stack b to make sure i can get a bigger chunk in stack b that is going to be in order??

*/



/*

rust is a good language to learn

*/
