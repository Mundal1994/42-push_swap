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

/*
**	short stack sorting logic
**	reduce stack a to 3 digits. sort those 3 digits before you push the last two digits back
*/

static void	sorting_logic(t_stack *stack)
{
	if (stack->bottom - stack->top_a > 3)
	{
		push_and_update(stack, 'b');
	}
	else
	{
		if (stack->a[stack->top_a] > stack->a[stack->top_a + 1])
		{
			if (stack->b_empty == FALSE && stack->b[stack->top_b] < \
				stack->b[stack->top_b + 1] && stack->bottom - stack->top_b > 1)
				solve_and_print(stack, "ss");
			else
				solve_and_print(stack, "sa");
		}
		else if (stack->a[stack->top_a] < stack->a[stack->bottom - 1])
			rotate_stacks(stack);
	}
}

/*	initializes the loops of the short stack logic	*/

void	short_stack_logic(t_stack *stack)
{
	while (check_if_ordered(stack) != TRUE)
		sorting_logic(stack);
	while (stack->b_empty == FALSE)
	{
		if (stack->a[stack->bottom - 1] == stack->a_big && \
			stack->b[stack->top_b] > stack->a_big)
		{
			solve_and_print(stack, "pa");
			update_values(&stack->a[stack->top_a], &stack->a_small, \
			&stack->a_big);
			solve_and_print(stack, "ra");
		}
		push_and_update(stack, 'a');
	}
}
