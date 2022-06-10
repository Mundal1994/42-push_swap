/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rotate_push.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:13:39 by molesen           #+#    #+#             */
/*   Updated: 2022/05/18 11:13:41 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	switch_stacks(t_stack *stack, char c)
{
	if (c == 'a')
	{
		if (stack->b[stack->top_b] < stack->b[stack->top_b + 1] && stack->b[stack->top_b] > stack->b[stack->top_b + 2])
			solve_and_print(stack, "ss");
		else
			solve_and_print(stack, "sa");
	}
	else
	{
		if (stack->a[stack->top_a] > stack->a[stack->top_a + 1] && stack->a[stack->top_a + 1] != stack->ordered_small)
			solve_and_print(stack, "ss");
		else
			solve_and_print(stack, "sb");
	}
}
