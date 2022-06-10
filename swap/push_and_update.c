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

/*	updates biggest and smallest number in the stack that is being pushed to	*/

static void	update_values(int *c, int *small, int *big)
{
	if (c[0] > *big)
		*big = c[0];
	if (c[0] < *small)
		*small = c[0];
}

/*	function that makes sure right update functions are called	*/

static void	update_big_small_value(t_stack *stack, char c)
{
	if (c == 'a')
	{
		update_values(&stack->a[stack->top_a], &stack->a_small, &stack->a_big);
		if (stack->b_empty == TRUE)
		{
			stack->b_small = 2147483647;
			stack->b_big = -2147483648;
		}
		else if (stack->a[stack->top_a] == stack->b_big)
			update_big_nbr(stack->b, &stack->b_big, stack->bottom, stack->top_b);
		else if (stack->a[stack->top_a] == stack->b_small)
			update_small_nbr(stack->b, &stack->b_small, stack->bottom, stack->top_b);
	}
	else
	{
		update_values(&stack->b[stack->top_b], &stack->b_small, &stack->b_big);
		if (stack->b[stack->top_b] == stack->a_big)
			update_big_nbr(stack->a, &stack->a_big, stack->bottom, stack->top_a);
		else if (stack->b[stack->top_b] == stack->a_small)
			update_small_nbr(stack->a, &stack->a_small, stack->bottom, stack->top_a);
	}
}


int	calc_push_a_rotation(t_stack *stack, int nbr, int top_c)
{
	int	i;
	int	save;

	i = top_c;
	save = stack->bottom + 1;
	while (i < stack->bottom)
	{
		if (stack->a_small > nbr && stack->a[i] == stack->a_small)
		{
			save = i - top_c;
			break ;
		}
		else if (stack->a[i] > nbr && i == top_c && stack->a[i] == stack->a_small)// might remove this >> (nbr > stack->a_big && stack->a[i] == stack->a_big)
		{
			save = i - top_c;
			break ;
		}
		else if (nbr > stack->a_big && stack->a[i] == stack->a_big)
		{
			save = i - top_c;
			break ;
		}
		else if (stack->a[i] > nbr && stack->a[i - 1] < nbr)// might remove this >> (nbr > stack->a_big && stack->a[i] == stack->a_big)
		{
			save = i - top_c;
		}
		++i;
	}
//	}
	// if (stack->bottom - 1 == stack->top_b)
	// {	
	// 	first_small = FALSE;
	// }
	//ft_printf("\nsave: %d, div: %d, nbr: %d\n", save, (((stack->bottom - top_c) / 2) + ((stack->bottom - top_c) % 2)), nbr);
	if (save == stack->bottom + 1)
		return (ERROR);
	if (save + 1 >= (((stack->bottom - top_c) / 2) + ((stack->bottom - top_c) % 2)))
		return (TRUE);
	return (FALSE);
}

/*something is wrong with above rotation logic*/

static void	push_and_update_helper(t_stack *stack, char c, int d)
{
	if (c == 'a')
	{
		d = calc_push_a_rotation(stack, stack->b[stack->top_b], stack->top_a);
		if (d == FALSE)
		{
			if (stack->a_small > stack->b[stack->top_b] || stack->a_big < stack->b[stack->top_b])
			{
				while (stack->a[stack->bottom - 1] != stack->a_big)
					solve_and_print(stack, "ra");
			}
			else if (stack->a_small > stack->b[stack->top_b] || stack->a_big < stack->b[stack->top_b])
			{
				while (stack->a[stack->bottom - 1] != stack->a_big)
					solve_and_print(stack, "ra");
			}
			// else if (stack->ordered_big < stack->b[stack->top_b] && stack->ordered_small <= stack->ordered_big)
			// {
			// 	while (stack->a[stack->bottom - 1] != stack->ordered_big)
			// 	{
			// 		solve_and_print(stack, "ra");
			// 	}
			// }
			// else if (stack->ordered_small > stack->b[stack->top_b] && stack->ordered_small <= stack->ordered_big)
			// {
			// 	while (stack->a[stack->top_a] != stack->ordered_small)
			// 	{
			// 		solve_and_print(stack, "ra");
			// 	}
			// }
			else
			{
				while (!(stack->a[stack->top_a] > stack->b[stack->top_b] && stack->a[stack->bottom - 1] < stack->b[stack->top_b]))
				{
					solve_and_print(stack, "ra");
				}
			}
		}
		else if (d == TRUE)
		{
			if (stack->a_small > stack->b[stack->top_b] || stack->a_big < stack->b[stack->top_b])
			{
				while (stack->a[stack->bottom - 1] != stack->a_big)
					solve_and_print(stack, "rra");
			}
			// else if (stack->ordered_big < stack->b[stack->top_b] && stack->ordered_small <= stack->ordered_big)
			// {
			// 	while (stack->a[stack->bottom - 1] != stack->ordered_big)
			// 		solve_and_print(stack, "rra");
			// }
			// else if (stack->ordered_small > stack->b[stack->top_b] && stack->ordered_small <= stack->ordered_big)
			// {
			// 	while (stack->a[stack->top_a] != stack->ordered_small)
			// 		solve_and_print(stack, "rra");
			// }
			else
			{
				while (!((stack->a[stack->bottom - 1] < stack->b[stack->top_b] && stack->a[stack->top_a] > stack->b[stack->top_b])))// || stack->a[stack->bottom - 1] == stack->a_small) && stack->a[stack->top_a] < stack->b[stack->top_b]))//stack->a[stack->bottom - 1] > stack->b[stack->top_b])
					solve_and_print(stack, "rra");
			}
		}
		solve_and_print(stack, "pa");
		if (stack->ordered_small > stack->a[stack->top_a])
			stack->ordered_small = stack->a[stack->top_a];
		if (stack->ordered_big < stack->a[stack->top_a])
		{
			int i = stack->top_a;
			stack->ordered_big = stack->a[stack->top_a];
			while (stack->a[i] < stack->a[i + 1])
			{
				stack->ordered_big = stack->a[i + 1];
				++i;
			}
		}
		if (stack->top_b == stack->bottom)//means one element left
		{
			stack->b_small = 2147483647;
			stack->b_big = -2147483648;
		}
	}
	else
	{
		solve_and_print(stack, "pb");
		if (stack->b_small > stack->b_big)
		{
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
		update_big_small_value(stack, c);
	}
	else
	{
		push_and_update_helper(stack, c, 0);
		update_big_small_value(stack, c);
	}
}