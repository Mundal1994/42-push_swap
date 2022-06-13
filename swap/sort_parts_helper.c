/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_parts_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:36:10 by molesen           #+#    #+#             */
/*   Updated: 2022/06/13 17:36:12 by molesen          ###   ########.fr       */
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
