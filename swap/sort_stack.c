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
	int	i;

	i = stack->top_a;
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

static int	stack_contain_nbrs(t_stack *stack, int nbr, int equal)
{
	int	i;

	i = stack->top_b;
	while (i < stack->bottom)
	{
		if (stack->b[i] > nbr && equal == FALSE)
			return (TRUE);
		if (stack->b[i] >= nbr && equal == TRUE)
			return (TRUE);
		++i;
	}
	return (FALSE);
}

/*	calls the functions that are behind the logic of the sorting	*/

void	sort_stack(t_stack *stack)
{
	int	multi;

	if (check_if_solved(stack) == ERROR)
	{
		if (stack->bottom < 20)
			short_stack_logic(stack);
		else
		{
			longest_list(stack);
			split_stack(stack);
			if (stack->list)
				free(stack->list);
			if (stack->bottom < 250)
				multi = 6;
			else
				multi = 10;
			if (stack_contain_nbrs(stack, stack->small_heigh, FALSE) == TRUE)
				sort_smallest(stack, (stack->small_heigh - stack->small_low) / multi, multi);
			if (stack_contain_nbrs(stack, stack->big_low, TRUE) == TRUE)
				sort_middle(stack, (stack->big_low - stack->small_heigh) / multi, multi);
			if (stack->b_empty == FALSE)
				sort_biggest(stack, (stack->big_heigh - stack->big_low) / multi, multi);
		}
		stack_rotate_init(stack);
	}
}
