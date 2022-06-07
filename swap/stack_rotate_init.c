/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rotate_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:23:03 by molesen           #+#    #+#             */
/*   Updated: 2022/05/18 10:23:04 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	calculates quickest way to get a specific number to be at the bottom
**	or find index where a number from one stack would fit into another
*/

int	calc_rr_or_rrr(t_stack *stack, int nbr, int top_c, char c)
{
	int	i;
	int	save;

	i = top_c;
	save = stack->bottom + 1;
	/*
	if (stack->a[i] < nbr && stack->a[stack->bottom - 1] > nbr && c == 'a')
		save = i - top_c;
	else if (stack->b[i] < nbr && stack->b[stack->bottom - 1] > nbr && c == 'b')
		save = i - top_c;*/
	//ft_printf("save: %d, median: %d, median_nbr: %d, bottom median: %d\n", save, stack->median, stack->median_nbr, (((stack->bottom - top_c) / 2) + ((stack->bottom - top_c) % 2)));
	while (i < stack->bottom)
	{
		if (stack->a[stack->top_a] < nbr && stack->a[stack->bottom - 1] > nbr && c == 'a')
			save = 0;
		else if (stack->b[stack->top_b] > nbr && stack->b[stack->bottom - 1] < nbr && c == 'b')
			save = 0;
		else if (c == 'b' && ((stack->b[i] > nbr && stack->b[i + 1] < nbr) || \
		(nbr > stack->b_big && stack->b[i] == stack->b_big)))// might remove this >> (nbr > stack->b_big && stack->b[i] == stack->b_big)
			save = i - top_c;//not sure this has to be minus top_c
		else if (c == 'a' && ((stack->a[i] < nbr && stack->a[i + 1] > nbr) || \
		(nbr > stack->a_big && stack->a[i] == stack->a_big)))// might remove this >> (nbr > stack->a_big && stack->a[i] == stack->a_big)
			save = i - top_c;
		if ((stack->a[i] == nbr && c == 'a') || (stack->b[i] == nbr && c == 'b'))
		{
			save = i - top_c;
			break ;
		}
		++i;
	}
	//ft_printf("\nsave: %d, median: %d, median_nbr: %d, bottom median: %d, nbr: %d\n", save, stack->median, stack->median_nbr, (((stack->bottom - top_c) / 2) + ((stack->bottom - top_c) % 2)), nbr);
	if (save == stack->bottom + 1)
		return (ERROR);
	if (save + 1 >= (((stack->bottom - top_c) / 2) + ((stack->bottom - top_c) % 2)))
		return (TRUE);
	return (FALSE);
}

/*	stack a or b in focus	*/
void	solve_and_print(t_stack *stack, char *str)
{
	solve_stack(stack, str);
	ft_putstr(str);
	ft_putchar('\n');
}

/*	rotates based on stack	*/

static void	solve_based_on_stack(t_stack *stack, char a)
{
//	int i;
	if (a == 'a')
	{
		// if (stack->b_empty == FALSE && b[stack->bottom - 1] > b[top_b])
		// 	solve_and_print(stack, "rr");
		// else
			solve_and_print(stack, "ra");
	}
	else
	{
		// if (b[stack->bottom - 1] < b[top_b])
		// 	i = 0;
		//	solve_and_print(stack, "rr");
		//else
			solve_and_print(stack, "rb");
	}
}

/*	narrows down which direction to rotate	*/

void	rotate_stacks(t_stack *stack, char c, char a)
{
	if (c == 'r')
	{
		if (a == 'a')
			solve_based_on_stack(stack, a);
		else
			solve_based_on_stack(stack, a);
	}
	else
	{
		if (a == 'a')
		{
			// if (stack->b_empty == FALSE && stack->b[stack->bottom - 1] > stack->b[stack->top_b])
			// 	solve_and_print(stack, "rrr");
			// else
				solve_and_print(stack, "rra");
		}
		else
		{
			// if (stack->a[stack->bottom - 1] < stack->a[stack->top_a])
			// 	solve_and_print(stack, "rrr");
			// else
			solve_and_print(stack, "rrb");
		}
	}
}

/*	rotates everything so biggest or smallest number is at the bottom	*/

void	stack_rotate_init(t_stack *stack, int *a, int nbr, char c)
{
	int	d;
	if (c == 'a')
	{
		d = calc_rr_or_rrr(stack, nbr, stack->top_a, 'a');
		if (d == FALSE)
			while (a[stack->bottom - 1] < a[stack->top_a])
				stack_rotate_push(stack, c, 'r');
		else if (d == TRUE)
			while (a[stack->bottom - 1] < a[stack->top_a])
				stack_rotate_push(stack, c, 'd');
	}
	else
	{
		d = calc_rr_or_rrr(stack, nbr, stack->top_b, 'b');
		if (d == FALSE)
			while (a[stack->bottom - 1] > a[stack->top_b])
				stack_rotate_push(stack, c, 'r');
		else if (d == TRUE)
			while (a[stack->bottom - 1] > a[stack->top_b])
				stack_rotate_push(stack, c, 'd');
	}
}