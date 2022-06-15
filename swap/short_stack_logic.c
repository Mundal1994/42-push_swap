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


static void	sorting_logic(t_stack *stack)
{
	if (stack->a[stack->top_a] > stack->a[stack->top_a + 1])
	{
		if (stack->b_empty == FALSE && stack->b[stack->top_b] < stack->b[stack->top_b + 1])
			solve_and_print(stack, "ss");
		else
			solve_and_print(stack, "sa");
	}
	else if (stack->a[stack->top_a] > stack->a[stack->bottom - 1])
	{
		solve_and_print(stack, "rra");
	}
	else if (stack->a[stack->top_a] < stack->a[stack->bottom - 1] && stack->a[stack->top_a + 1] > stack->a[stack->bottom - 1])
	{
		push_and_update(stack, 'b');
		solve_and_print(stack, "rra");
	}
	else if (stack->a[stack->top_a] < stack->a[stack->bottom - 1] && stack->a[stack->top_a + 1] < stack->a[stack->bottom - 1])
	{
		solve_and_print(stack, "rra");
		push_and_update(stack, 'b');
	}
}

void	short_stack_logic(t_stack *stack)
{
	while (check_if_ordered(stack) != TRUE)
		sorting_logic(stack);
	while (stack->b_empty == FALSE)
		push_and_update(stack, 'a');
}
