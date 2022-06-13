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

void	rotate_based_on_calc(t_stack *stack, int calc, char c)
{
	int	d;

	if (c == 'r')
	{
		d = calc_push_a_rotation(stack, stack->b[find_index(stack, \
		stack->top_b + 1, calc, 'r')], stack->top_a);
		if (d == FALSE)
			solve_and_print(stack, "rr");
		else
			solve_and_print(stack, "rb");
	}
	else
	{
		d = calc_push_a_rotation(stack, stack->b[find_index(stack, \
		stack->bottom - 1, calc, 'd')], stack->top_a);
		if (d == TRUE)
			solve_and_print(stack, "rrr");
		else
			solve_and_print(stack, "rrb");
	}
}

void	sort_middle(t_stack *stack, int calc, int multi)
{
	int first;
	int mid_calc;

	--multi;
	mid_calc = stack->big_low - (calc * multi--);
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
/*	apply same rotation logic to middle and small numbers	*/

void	sort_biggest(t_stack *stack, int calc, int multi)
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
	if (stack->b[stack->bottom - 1] > stack->small_heigh)
	{
		rotate_based_on_calc(stack, big_calc, 'd');
		push_and_update(stack, 'a');
	}
}
