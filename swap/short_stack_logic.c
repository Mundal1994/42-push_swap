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

/*
**	checks if everything is ordered in stack a
**	takes into consideration that stack might need to rotate
*/

int	check_if_ordered(t_stack *stack)
{
	int	i;

	i = stack->top_a;
	while (i < stack->bottom && stack->a[i] != stack->a_small)
		++i;
	if (stack->top_a != i && stack->a[stack->bottom - 1] > stack->a[stack->top_a])
		return (ERROR);
	++i;
	while (i < stack->bottom)
	{
		if (stack->a[i] < stack->a[i - 1])
			return (ERROR);
		++i;
	}
	if (stack->a[stack->top_a] != stack->a_small)
	{
		i = stack->top_a + 1;
		while (stack->a[i] != stack->a_small)
		{
			if (stack->a[i] < stack->a[i - 1])
				return (ERROR);
			++i;
		}
	}
	return (TRUE);
}

/*	short stack sorting logic	*/

static void	sorting_logic(t_stack *stack)
{
	if (stack->a[stack->top_a] > stack->a[stack->top_a + 1])
	{
		if (stack->b_empty == FALSE && stack->b[stack->top_b] < \
			stack->b[stack->top_b + 1])
			solve_and_print(stack, "ss");
		else
			solve_and_print(stack, "sa");
	}
	else if (stack->a[stack->top_a] > stack->a[stack->bottom - 1])
		solve_and_print(stack, "rra");
	else if (stack->a[stack->top_a] < stack->a[stack->bottom - 1] && \
		stack->a[stack->top_a + 1] > stack->a[stack->bottom - 1])
	{
		push_and_update(stack, 'b');
		solve_and_print(stack, "rra");
	}
	else if (stack->a[stack->top_a] < stack->a[stack->bottom - 1] && \
		stack->a[stack->top_a + 1] < stack->a[stack->bottom - 1])
	{
		solve_and_print(stack, "rra");
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
