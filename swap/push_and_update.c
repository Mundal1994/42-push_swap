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

static void	smallest_number(int *c, int *small, int len, int top_c)
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

static void	biggest_number(int *c, int *big, int len, int top_c)
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

static void	update_big_small(int *c, int *small, int *big)
{
	if (c[0] > *big)
		*big = c[0];
	if (c[0] < *small)
		*small = c[0];
}

static void	push_and_update_helper(t_stack *stack, char c, int d)
{
	if (c == 'a')
	{
		if (stack->a_small > stack->b[stack->top_b] || stack->a_big < stack->b[stack->top_b])
			stack_rotate_init(stack, stack->a, stack->a_big, 'a');
		else
		{
			d = calc_rr_or_rrr(stack, stack->b[stack->top_b], stack->top_a, 'a');
			if (d == FALSE && stack->b[stack->top_b] < stack->a_big)
				while (stack->a[stack->top_a] < stack->b[stack->top_b])
					solve_and_print(stack, "ra");
			else if (d == TRUE && stack->b[stack->top_b] < stack->a_big)
				while (!((stack->a[stack->bottom - 1] > stack->b[stack->top_b] || stack->a[stack->bottom - 1] == stack->a_small) && stack->a[stack->top_a] < stack->b[stack->top_b]))//stack->a[stack->bottom - 1] > stack->b[stack->top_b])
					solve_and_print(stack, "rra");
		}
		solve_and_print(stack, "pa");
		if (stack->b_small == stack->b_big)//means one element left
		{
			stack->b_empty = TRUE;
			stack->b_small = 2147483647;
			stack->b_big = -2147483648;
		}
	}
	else
	{
		if (stack->b_small > stack->a[stack->top_a] || \
		stack->b_big < stack->a[stack->top_a])
			stack_rotate_init(stack, stack->b, stack->b_small, 'b');
		else
		{
			d = calc_rr_or_rrr(stack, stack->a[stack->top_a], stack->top_b, 'b');
			//ft_printf("d = %d\n", d);
			if (d == FALSE && stack->b_empty == FALSE)// && stack->a[stack->top_a] < stack->b_big && stack->b_big > stack->b_small)
				while (stack->b[stack->top_b] > stack->a[stack->top_a])
					solve_and_print(stack, "rb");
			else if (d == TRUE && stack->b_empty == FALSE)// && stack->a[stack->top_a] < stack->b_big && stack->b_big > stack->b_small)
			{
				//ft_printf("inside d true\nstack[bottom]: %d, stack->a[top]: %d", stack->b[stack->bottom - 1], stack->a[stack->top_a]);
				while (!((stack->b[stack->bottom - 1] > stack->a[stack->top_a] || stack->b[stack->bottom - 1] == stack->b_small) && stack->b[stack->top_b] < stack->a[stack->top_a]))//stack->b[stack->bottom - 1] < stack->a[stack->top_a] || (stack->b[stack->bottom - 1] > stack->a[stack->top_a] && stack->b[stack->top_b] > stack->a[stack->top_a]))
				{
					//ft_printf("inside loop\n");
					solve_and_print(stack, "rrb");}
			}
		}
		solve_and_print(stack, "pb");
		if (stack->b_small > stack->b_big)//means stack is empty
		{
			stack->b_empty = FALSE;
			stack->b_small = stack->b[stack->bottom - 1];
			stack->b_big = stack->b[stack->top_b];
		}
	}
}

void	push_and_update(t_stack *stack, char c)
{
	if (c == 'a')
	{
		push_and_update_helper(stack, c, 0);
		update_big_small(&stack->a[stack->top_a], &stack->a_small, &stack->a_big);
		if (stack->a[stack->top_a] == stack->b_big)
			biggest_number(stack->b, &stack->b_big, stack->bottom, stack->top_b);
		else if (stack->a[stack->top_a] == stack->b_small)
			smallest_number(stack->b, &stack->b_small, stack->bottom, stack->top_b);
	}
	else
	{
		push_and_update_helper(stack, c, 0);
		update_big_small(&stack->b[stack->top_b], &stack->b_small, &stack->b_big);
		if (stack->b[stack->top_b] == stack->a_big)
			biggest_number(stack->a, &stack->a_big, stack->bottom, stack->top_a);
		else if (stack->b[stack->top_b] == stack->a_small)
			smallest_number(stack->a, &stack->a_small, stack->bottom, stack->top_a);
	}
	// maybe makes most sense here to check if stack b is sorted or not?? or maybe after moving stuff?
}