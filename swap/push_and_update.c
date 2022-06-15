/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_and_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:42:52 by molesen           #+#    #+#             */
/*   Updated: 2022/05/18 11:42:54 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*	updates smallest number in the stack that is being pushed from	*/

static void	update_small_nbr(int *c, int *small, int len, int top_c)
{
	int	i;

	i = top_c;
	*small = c[top_c];
	while (i < len)
	{
		if (c[i] < *small)
			*small = c[i];
		++i;
	}
}

/*	updates biggest number in the stack that is being pushed from	*/

static void	update_big_nbr(int *c, int *big, int len, int top_c)
{
	int	i;

	i = top_c;
	*big = c[top_c];
	while (i < len)
	{
		if (c[i] > *big)
			*big = c[i];
		++i;
	}
}

/*	updates biggest and smallest nbr in the stack that is being pushed to	*/

static void	update_values(int *c, int *small, int *big)
{
	if (c[0] > *big)
		*big = c[0];
	if (c[0] < *small)
		*small = c[0];
}

/*	rotation logic and updating correct values	*/

void	push_and_update(t_stack *stack, char c)
{
	if (c == 'a')
	{
		push_to_stack(stack, c);
		update_values(&stack->a[stack->top_a], &stack->a_small, &stack->a_big);
	}
	else
	{
		push_to_stack(stack, c);
		if (stack->b[stack->top_b] == stack->a_big)
			update_big_nbr(stack->a, &stack->a_big, stack->bottom, \
			stack->top_a);
		else if (stack->b[stack->top_b] == stack->a_small)
			update_small_nbr(stack->a, &stack->a_small, stack->bottom, \
			stack->top_a);
	}
}
