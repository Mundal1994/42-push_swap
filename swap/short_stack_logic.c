/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_stack_logic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:55:58 by molesen           #+#    #+#             */
/*   Updated: 2022/06/15 11:56:00 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*	rotates stacks at the same time	*/

static void	rotate_stacks(t_stack *stack)
{
	if (stack->b_empty == FALSE && stack->b[stack->top_b] < \
		stack->b[stack->top_b + 1] && stack->bottom - stack->top_b > 1)
		solve_and_print(stack, "rrr");
	else
		solve_and_print(stack, "rra");
}

/*	check if there is a number that fits between two values	*/

static int	next_in_line(t_stack *stack)
{
	int	i;

	i = stack->top_a + 1;
	while (i < stack->bottom)
	{
		if (stack->a[i] > stack->a[stack->top_a] && stack->a[i] < \
			stack->a[stack->bottom - 1])
			return (FALSE);
		++i;
	}
	i = stack->top_b;
	while (i < stack->bottom && stack->b_empty == FALSE)
	{
		if (stack->b[i] > stack->a[stack->top_a] && stack->b[i] < \
			stack->a[stack->bottom - 1])
			return (FALSE);
		++i;
	}
	return (TRUE);
}

/*	logic of choosing between switching or pushing to stack b	*/

static void	push_or_switch(t_stack *stack, int swap)
{
	int	next;

	next = next_in_line(stack);
	if (swap == FALSE)
	{
		if (next == FALSE)
			push_and_update(stack, 'b');
		rotate_stacks(stack);
	}
	if (next == TRUE || swap == TRUE)
	{
		if (stack->b_empty == FALSE && stack->b[stack->top_b] < \
			stack->b[stack->top_b + 1] && stack->bottom - stack->top_b > 1)
			solve_and_print(stack, "ss");
		else
			solve_and_print(stack, "sa");
	}
}

/*	short stack sorting logic	*/

static void	sorting_logic(t_stack *stack)
{
	if (stack->a[stack->top_a] > stack->a[stack->top_a + 1])
		push_or_switch(stack, TRUE);
	else if (stack->a[stack->top_a] < stack->a[stack->bottom - 1] && \
		stack->a[stack->top_a + 1] < stack->a[stack->bottom - 1] && \
		stack->a[stack->top_a + 2] > stack->a[stack->bottom - 1])
	{
		push_and_update(stack, 'b');
		rotate_stacks(stack);
		solve_and_print(stack, "sa");
	}
	else if (stack->a[stack->top_a] > stack->a[stack->bottom - 1])
		rotate_stacks(stack);
	else if (stack->a[stack->top_a] < stack->a[stack->bottom - 1] && \
		stack->a[stack->top_a + 1] > stack->a[stack->bottom - 1])
		push_or_switch(stack, FALSE);
	else if (stack->a[stack->top_a] < stack->a[stack->bottom - 1] && \
		stack->a[stack->top_a + 1] < stack->a[stack->bottom - 1])
	{
		rotate_stacks(stack);
		push_and_update(stack, 'b');
	}
}

/*	initializes the loops of the short stack logic	*/

void	short_stack_logic(t_stack *stack)
{
	while (check_if_ordered(stack) != TRUE)
		sorting_logic(stack);
	while (stack->b_empty == FALSE)
		push_and_update(stack, 'a');
}
