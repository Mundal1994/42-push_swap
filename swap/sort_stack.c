/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:23:32 by molesen           #+#    #+#             */
/*   Updated: 2022/05/18 10:23:34 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	checks if everything is ordered in stack a
**	takes into consideration that stack might need to rotate
*/

static int	check_if_ordered(t_stack *stack)
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

/*	checks if nbr is part of the already sorted list	*/

static int	is_list(t_stack *stack, int nbr)
{
	int	i;

	i = 0;
	while (i < stack->len)
	{
		if (nbr == stack->list[i])
			return (i);
		++i;
	}
	return (-1);
}

/*
**	checks if we have sorted it correctly
**	sorted list and small numbers on stack a and everything else on stack b
*/

static int	is_sorted(t_stack *stack)
{
	int i = stack->top_a;

	while (i < stack->bottom)
	{
		if (stack->a[i] > stack->small_heigh && is_list(stack, stack->a[i]) < 0)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

static void	split_stack(t_stack *stack)
{
	while (is_sorted(stack) == FALSE)
	{
		if (stack->a[stack->top_a] > stack->small_heigh && \
			stack->a[stack->top_a] < stack->big_low && \
			is_list(stack, stack->a[stack->top_a]) < 0)
			push_and_update(stack, 'b');
		else if (stack->a[stack->top_a] >= stack->big_low && \
			is_list(stack, stack->a[stack->top_a]) < 0)
		{
			push_and_update(stack, 'b');
			if (stack->a[stack->top_a] <= stack->small_heigh)
				solve_and_print(stack, "rr");
			else
				solve_and_print(stack, "rb");
		}
		else
			solve_and_print(stack, "ra");
	}
	while (check_if_ordered(stack) != TRUE)
	{
		if (is_list(stack, stack->a[stack->top_a]) < 0)
			push_and_update(stack, 'b');
		else
			solve_and_print(stack, "ra");
	}
}

void	sort_stack(t_stack *stack)
{
	int	multi;

	if (check_if_solved(stack) == ERROR)
	{
		longest_list(stack);
		split_stack(stack);
		if (stack->list)
			free(stack->list);
		if (stack->bottom < 50)
			multi = 2;
		else if (stack->bottom < 250)
			multi = 6;
		else
			multi = 10;
		sort_smallest(stack, (stack->small_heigh - stack->small_low) / multi, multi);
		sort_middle(stack, (stack->big_low - stack->small_heigh) / multi, multi);
		sort_biggest(stack, (stack->big_heigh - stack->big_low) / multi, multi);
		stack_rotate_init(stack);
	}
}
