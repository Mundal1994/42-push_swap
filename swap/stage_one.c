/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stage_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:53:06 by molesen           #+#    #+#             */
/*   Updated: 2022/05/18 11:53:08 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// might not be relevant anymore because of the median stage 2
/*static void	switch_two_bottom_nbr(t_stack *stack)
{
	if (stack->b[stack->bottom - 2] == stack->b_big && \
	stack->b[stack->bottom - 1] == stack->b_small && stack->bottom - \
	stack->top_b > 4 && stack->a[stack->bottom - 2] == stack->a_small && \
	stack->a[stack->bottom - 1] == stack->a_big && stack->bottom - stack->top_a \
	> 4)
	{
		solve_and_print(stack, "rrr");
		solve_and_print(stack, "rrr");
		solve_and_print(stack, "ss");
		solve_and_print(stack, "rr");
	}
	else
	{
		solve_and_print(stack, "rra");
		solve_and_print(stack, "rra");
		solve_and_print(stack, "sa");
		solve_and_print(stack, "ra");
	}
}*/
/*
static void	smaller_than_stack_b(t_stack *stack)
{
	push_and_update(stack, 'b');
	if (stack->a[stack->top_a] > stack->a[stack->top_a + 1])
		switch_stacks(stack, 'a');
	else
		switch_stacks(stack, 'b');
}
*/
/*
static void	bottom_replace_top(t_stack *stack)
{
	if (stack->bottom - stack->top_a < 5)
	{
		rotate_stacks(stack, 'd', 'a');
		//switch_stacks(stack, 'a');
	}
	else
	{
		push_and_update(stack, 'b');
		//rotate_stacks(stack, 'd', 'a'); THIS MADE IT SO MUCH WORSE
		//if same can be done for stack b do rrr else
		//rotate_stacks(stack, 'd', 'a');
	}
}*/

void	stage_one_split(t_stack *stack)
{
	if (stack->bottom - stack->top_b > 20)
	{
		while (stack->b_empty == FALSE)
			push_and_update(stack, 'a');
	}
	else
		push_and_update(stack, 'b');
}
