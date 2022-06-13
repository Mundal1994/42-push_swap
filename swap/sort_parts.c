/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_parts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:06:58 by molesen           #+#    #+#             */
/*   Updated: 2022/06/10 17:07:01 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*	locates nearest index of number that is below value we are looking for	*/

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

/*
**	rotation logic that also will move stack a if stacks has to be moved
**	in both directions
*/

void	rotate_based_on_calc(t_stack *stack, int value, char c)
{
	int	d;

	if (c == 'r')
	{
		d = push_a_rotation_logic(stack, stack->b[find_index(stack, \
		stack->top_b + 1, value, 'r')]);
		if (d == FALSE)
			solve_and_print(stack, "rr");
		else
			solve_and_print(stack, "rb");
	}
	else
	{
		d = push_a_rotation_logic(stack, stack->b[find_index(stack, \
		stack->bottom - 1, value, 'd')]);
		if (d == TRUE)
			solve_and_print(stack, "rrr");
		else
			solve_and_print(stack, "rrb");
	}
}

/*	push or rotate stack based on number that has been calculated	*/

static void	push_to_a_or_rotate(t_stack *stack, int first, int value)
{
	if (first == TRUE && stack->b[stack->top_b] <= value)
		push_and_update(stack, 'a');
	else if (first == TRUE)
		rotate_based_on_calc(stack, value, 'r');
	else if (first == FALSE && stack->b[stack->top_b] <= value)
		push_and_update(stack, 'a');
	else if (first == FALSE)
		rotate_based_on_calc(stack, value, 'd');
}

/*	rotation logic for stack b small numbered section	*/

void	sort_smallest(t_stack *stack, int calc, int multi)
{
	int	first;
	int small_calc;

	--multi;
	small_calc = stack->small_heigh - (calc * multi--);
	first = TRUE;
	while (multi >= -1)
	{
		push_to_a_or_rotate(stack, first, small_calc);
		if (first == FALSE && stack->b[stack->bottom - 1] > stack->small_heigh)
		{
			small_calc = stack->small_heigh - (calc * multi--);
			first = TRUE;
		}
		else if (first == TRUE && stack->b[stack->top_b] > stack->small_heigh)
		{
			first = FALSE;
			small_calc = stack->small_heigh - (calc * multi--);
			rotate_based_on_calc(stack, small_calc, 'd');
		}
	}
}

/*	rotation logic for stack b middle numbered section	*/

void	sort_middle(t_stack *stack, int calc, int multi)
{
	int first;
	int mid_calc;

	--multi;
	mid_calc = stack->big_low - (calc * multi--);
	first = TRUE;
	while (multi >= -1)
	{
		push_to_a_or_rotate(stack, first, mid_calc);
		if (first == FALSE && stack->b[stack->bottom - 1] >= stack->big_low)
		{
			mid_calc = stack->big_low - (calc * multi--);
			first = TRUE;
		}
		else if (first == TRUE && stack->b[stack->top_b] >= stack->big_low)
		{
			first = FALSE;
			mid_calc = stack->big_low - (calc * multi--);
			rotate_based_on_calc(stack, mid_calc, 'd');
		}
	}
}
