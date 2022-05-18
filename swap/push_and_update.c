/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_and_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:42:52 by molesen           #+#    #+#             */
/*   Updated: 2022/05/18 11:42:54 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	smallest_number(int *a, int *small, int len)
{
	int	i;

	i = 0;
	*small = a[0];
	while (i++ < len)
	{
		if (a[i] < *small)
			*small = a[i];
	}
}

static void	biggest_number(int *a, int *big, int len)
{
	int	i;

	i = 0;
	*big = a[0];
	while (i++ < len)
	{
		if (a[i] > *big)
			*big = a[i];
	}
}

static void	update_big_small(int *a, int *small, int *big)
{
	if (a[0] > *big)
		*big = a[0];
	else if (a[0] < *small)
		*small = a[0];
}

static void	push_and_update_helper(t_stack *stack, char c, int d)
{
	if (c == 'a')
	{
		if (stack->b_small == stack->b_big)//means one element left
		{
			stack->b_small = 1;
			stack->b_big = -1;
		}
		solve_and_print(stack, "pa");
	}
	else
	{
		d = calc_rr_or_rrr(stack, stack->b, stack->a[stack->top_a], stack->top_b);
		if (d == FALSE && stack->b_empty == FALSE && stack->a[stack->top_a] < stack->b_big && stack->b_big > stack->b_small)
			while (stack->b[stack->top_b] > stack->a[stack->top_a])
				solve_and_print(stack, "rb");
		else if (d == TRUE && stack->b_empty == FALSE && stack->a[stack->top_a] < stack->b_big && stack->b_big > stack->b_small)
			while (stack->b[stack->bottom - 1] < stack->a[stack->top_a])
				solve_and_print(stack, "rrb");
		solve_and_print(stack, "pb");
		if (stack->b_small > stack->b_big)//means stack is empty
		{
			stack->b_small = stack->b[stack->bottom - 1];
			stack->b_big = stack->b[stack->top_b];
		}
	}
}

void	push_and_update(t_stack *stack, char c)
{
	if (c == 'a')
	{
		push_and_update_helper(stack, c, 0);
		update_big_small(&stack->a[stack->top_a], &stack->a_small, &stack->a_big);
		if (stack->a[stack->top_a] == stack->b_big)
			biggest_number(stack->b, &stack->b_big, stack->bottom - stack->top_b);
		else if (stack->a[stack->top_a] == stack->b_small)
			smallest_number(stack->b, &stack->b_small, stack->bottom - stack->top_b);
	}
	else
	{
		push_and_update_helper(stack, c, 0);
		update_big_small(&stack->b[stack->top_b], &stack->b_small, &stack->b_big);
		if (stack->b[stack->top_b] == stack->a_big)
			biggest_number(stack->a, &stack->a_big, stack->bottom - stack->top_a);
		else if (stack->b[stack->top_b] == stack->a_small)
			smallest_number(stack->a, &stack->a_small, stack->bottom - stack->top_a);
	}
	// maybe makes most sense here to check if stack b is sorted or not?? or maybe after moving stuff?
}