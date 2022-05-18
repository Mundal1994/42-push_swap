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

/*	calculates quickest way to get a specific number to be at the bottom	*/

int	calc_rr_or_rrr(t_stack *stack, int *a, int nbr, int top_a)
{
	int	i;
	int	found;
	int	save;

	found = FALSE;
	i = top_a;
	while (i < stack->bottom)
	{
		if (a[i] > nbr && a[i + 1] < nbr)
			save = i;
		if (a[i] == nbr)
		{
			save += i + 1;
			found = TRUE;
			break ;
		}
		++i;
	}
	if (save == stack->bottom)
		return (ERROR);
	if (save > (((stack->bottom - top_a) / 2) + ((stack->bottom - top_a) % 2)))
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

static void	solve_based_on_stack(t_stack *stack, int *b, int top_b, char a)
{
	if (a == 'a')
	{
		if (stack->b_empty == FALSE && b[stack->bottom - 1] > b[top_b])
			solve_and_print(stack, "rr");
		else
			solve_and_print(stack, "ra");
	}
	else
	{
		if (b[stack->bottom - 1] < b[top_b])
			solve_and_print(stack, "rr");
		else
			solve_and_print(stack, "rb");
	}
}

/*	narrows down which direction to rotate	*/

void	rotate_stacks(t_stack *stack, char c, char a)
{
	if (c == 'r')
	{
		if (a == 'a')
			solve_based_on_stack(stack, stack->b, stack->top_b, a);
		else
			solve_based_on_stack(stack, stack->a, stack->top_a, a);
	}
	else
	{
		if (a == 'a')
		{
			if (stack->b_empty == FALSE && stack->b[stack->bottom - 1] > stack->b[stack->top_b])
				solve_and_print(stack, "rrr");
			else
				solve_and_print(stack, "rra");
		}
		else
		{
			if (stack->a[stack->bottom - 1] < stack->a[stack->top_a])
				solve_and_print(stack, "rrr");
			else
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
		d = calc_rr_or_rrr(stack, a, nbr, stack->top_a);
		if (d == FALSE)
			while (a[stack->bottom - 1] < a[stack->top_a])
				stack_rotate_push(stack, c, 'r');
		else if (d == TRUE)
			while (a[stack->bottom - 1] < a[stack->top_a])
				stack_rotate_push(stack, c, 'd');
		//we have stack a as the focus
	}
	else
	{
		d = calc_rr_or_rrr(stack, a, nbr, stack->top_b);
		if (d == FALSE)
			while (a[stack->bottom - 1] > a[stack->top_b])
				stack_rotate_push(stack, c, 'r');
		else if (d == TRUE)
			while (a[stack->bottom - 1] > a[stack->top_b])
				stack_rotate_push(stack, c, 'd');
		//we have stack b as the focus
	}
}