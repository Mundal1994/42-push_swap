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
			return (ERROR);
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
	if (top_c != i && checks_order(stack, i, c_char, TRUE) == ERROR)
		return (error_start_nbr(stack, i, 'e'));
	++i;
	if (c_char == 'b')
		++i;
	while (i < stack->bottom)
	{
		if (checks_order(stack, i, c_char, FALSE) == ERROR)
			return (error_start_nbr(stack, i, 'e'));
		++i;
	}
	if ((c[top_c] != stack->a_small && c_char == 'a') || (c[top_c] != stack->b_big && c_char == 'b'))
	{
		i = top_c + 1;
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
		}
		++i;
	}
	stack->start_nbr = nbr;
	stack->a_small = small;
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

static int	find_index(t_stack *stack, int start, int value, int d)
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

static void	rotate_based_on_calc(t_stack *stack, int calc, char c)
{
	int	d;

	if (c == 'r')
	{
		d = calc_push_a_rotation(stack, stack->b[find_index(stack, stack->top_b + 1, calc, 'r')], stack->top_a);
		if (d == FALSE)
			solve_and_print(stack, "rr");
		else
			solve_and_print(stack, "rb");
	}
	else
	{
		d = calc_push_a_rotation(stack, stack->b[find_index(stack, stack->bottom - 1, calc, 'd')], stack->top_a);
		if (d == TRUE)
			solve_and_print(stack, "rrr");
		else
			solve_and_print(stack, "rrb");
	}
}

static void	sort_numbers_mid(t_stack *stack, int calc, int multi)
{
	int first;
	int mid_calc;

	--multi;
	mid_calc = stack->mid_heigh - (calc * multi--);
	first = TRUE;
	while (multi >= -1)
	{
		if (first == TRUE && stack->b[stack->top_b] <= mid_calc)
			push_and_update(stack, 'a');
		else if (first == TRUE)
			rotate_based_on_calc(stack, mid_calc, 'r');
		else if (first == FALSE && stack->b[stack->top_b] <= mid_calc && \
			stack->b[stack->top_b] > stack->small_heigh && stack->b[stack->top_b] \
			< stack->big_low)
			push_and_update(stack, 'a');
		else if (first == FALSE)
			rotate_based_on_calc(stack, mid_calc, 'd');
		if (first == FALSE && stack->b[stack->bottom - 1] <= stack->small_heigh)
		{
			mid_calc = stack->mid_heigh - (calc * multi--);
			first = TRUE;
		}
		else if (first == TRUE && stack->b[stack->top_b] >= stack->big_low)
		{
			first = FALSE;
			mid_calc = stack->mid_heigh - (calc * multi--);
			rotate_based_on_calc(stack, mid_calc, 'd');
		}
	}
}
/*	apply same rotation logic to middle and small numbers	*/

static void	sort_numbers_big(t_stack *stack, int calc, int multi)
{
	int	first;
	int big_calc;

	--multi;
	big_calc = stack->big_heigh - (calc * multi--);
	first = TRUE;
	while (multi >= -1)
	{
		if (first == TRUE && stack->b[stack->top_b] <= big_calc)
			push_and_update(stack, 'a');
		else if (first == TRUE)
			rotate_based_on_calc(stack, big_calc, 'r');
		else if (first == FALSE && stack->b[stack->top_b] <= big_calc && \
			stack->b[stack->top_b] >= stack->big_low)
			push_and_update(stack, 'a');
		else if (first == FALSE)
			rotate_based_on_calc(stack, big_calc, 'd');
		if (first == FALSE && stack->b[stack->bottom - 1] <= stack->small_heigh)
		{
			big_calc = stack->big_heigh - (calc * multi--);
			first = TRUE;
		}
		else if (first == TRUE && stack->b[stack->top_b] <= stack->small_heigh)
		{
			first = FALSE;
			big_calc = stack->big_heigh - (calc * multi--);
			rotate_based_on_calc(stack, big_calc, 'd');
		}
	}
	if (stack->b[stack->top_b] > stack->small_heigh)
	{
		rotate_based_on_calc(stack, big_calc, 'd');
		push_and_update(stack, 'a');
	}
}

static void	sort_numbers_small(t_stack *stack, int calc, int multi)
{
	int	check_nbr;
	int small_calc;

	check_nbr = 0;
	--multi;
	small_calc = stack->small_heigh - (calc * multi--);
	while (stack->b_empty == FALSE)
	{
		if (stack->b[stack->top_b] <= small_calc)
			push_and_update(stack, 'a');
		else
		{
			if (!check_nbr)
				check_nbr = stack->b[stack->top_b];
			rotate_based_on_calc(stack, small_calc, 'r');
		}
		if (stack->b[stack->top_b] == check_nbr)
		{
			small_calc = stack->small_heigh - (calc * multi);
			--multi;
		}
	}
}

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
				push_and_update(stack, 'b');
			else
				solve_and_print(stack, "ra");
		}
		longest_list(stack, 'a');
		while (check_if_ordered(stack, stack->a, stack->top_a, 'a') != TRUE)
		{
			if (islist(stack, stack->a[stack->top_a]) < 0)
				push_and_update(stack, 'b');
			else
				solve_and_print(stack, "ra");
		}
		int multi;
		
		if (stack->bottom < 50)
			multi = 2;
		if (stack->bottom < 250)
			multi = 4;
		else
			multi = 6;
		sort_numbers_mid(stack, (stack->mid_heigh - stack->mid_low) / multi, multi);
		sort_numbers_big(stack, (stack->big_heigh - stack->big_low) / multi, multi);
		sort_numbers_small(stack, (stack->small_heigh - stack->small_low) / multi, multi);
		stack_rotate_init(stack, stack->a, stack->a_big, 'a');
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
