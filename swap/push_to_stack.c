/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_stacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:18:42 by molesen           #+#    #+#             */
/*   Updated: 2022/06/13 17:18:44 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	keep_looking(t_stack *stack, int *save, int i, int nbr)
{
	if (stack->a_small > nbr && stack->a[i] == stack->a_small)
	{
		*save = i - stack->top_a;
		return (FALSE);
	}
	else if (stack->a[i] > nbr && i == stack->top_a && stack->a[i] == \
		stack->a_small)
	{
		*save = i - stack->top_a;
		return (FALSE);
	}
	else if (nbr > stack->a_big && stack->a[i] == stack->a_big)
	{
		*save = i - stack->top_a;
		return (FALSE);
	}
	else if (stack->a[i] > nbr && stack->a[i - 1] < nbr)
		*save = i - stack->top_a;
	return (TRUE);
}

/*	calculates which direction to rotate stack a before pushing from b	*/

int	push_a_rotation_logic(t_stack *stack, int nbr)
{
	int	i;
	int	save;

	i = stack->top_a;
	save = stack->bottom + 1;
	while (i < stack->bottom)
	{
		if (keep_looking(stack, &save, i, nbr) == FALSE)
			break ;
		++i;
	}
	if (save == stack->bottom + 1)
		return (ERROR);
	if (save + 1 >= (((stack->bottom - stack->top_a) / 2) + \
		((stack->bottom - stack->top_a) % 2)))
		return (TRUE);
	return (FALSE);
}

/*	rotating stack a logic	*/

static void	rotate_stack_a(t_stack *stack, int d)
{
	if (d == FALSE)
	{
		if (stack->a_small > stack->b[stack->top_b] || stack->a_big < \
			stack->b[stack->top_b])
			while (stack->a[stack->bottom - 1] != stack->a_big)
				solve_and_print(stack, "ra");
		else
			while (!(stack->a[stack->top_a] > stack->b[stack->top_b] && \
				stack->a[stack->bottom - 1] < stack->b[stack->top_b]))
				solve_and_print(stack, "ra");
	}
	else if (d == TRUE)
	{
		if (stack->a_small > stack->b[stack->top_b] || stack->a_big < \
			stack->b[stack->top_b])
			while (stack->a[stack->bottom - 1] != stack->a_big)
				solve_and_print(stack, "rra");
		else
			while (!((stack->a[stack->bottom - 1] < stack->b[stack->top_b] && \
				stack->a[stack->top_a] > stack->b[stack->top_b])))
				solve_and_print(stack, "rra");
	}
}

/*	does the logic for pushing to stack a and stack b	*/

void	push_to_stack(t_stack *stack, char c)
{
	int	d;

	if (c == 'a')
	{
		d = push_a_rotation_logic(stack, stack->b[stack->top_b]);
		rotate_stack_a(stack, d);
		solve_and_print(stack, "pa");
	}
	else
		solve_and_print(stack, "pb");
}
