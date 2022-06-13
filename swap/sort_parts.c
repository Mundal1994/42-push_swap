/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_parts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:06:58 by molesen           #+#    #+#             */
/*   Updated: 2022/06/10 17:07:01 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*	push or rotate stack based on number that has been calculated	*/

static void	push_to_a_or_rotate(t_stack *stack, int first, int value)
{
	if (first == TRUE && stack->b[stack->top_b] <= value)
		push_and_update(stack, 'a');
	else if (first == TRUE)
		rotate_based_on_calc(stack, value, 'r');
	else if (first == FALSE && stack->b[stack->top_b] <= value)
		push_and_update(stack, 'a');
	else if (first == FALSE)
		rotate_based_on_calc(stack, value, 'd');
}

/*	rotation logic for stack b small numbered section	*/

void	sort_smallest(t_stack *stack, int calc, int multi)
{
	int	first;
	int small_calc;

	--multi;
	small_calc = stack->small_heigh - (calc * multi--);
	first = TRUE;
	while (multi >= -1)
	{
		push_to_a_or_rotate(stack, first, small_calc);
		if (first == FALSE && stack->b[stack->bottom - 1] > stack->small_heigh)
		{
			small_calc = stack->small_heigh - (calc * multi--);
			first = TRUE;
		}
		else if (first == TRUE && stack->b[stack->top_b] > stack->small_heigh)
		{
			first = FALSE;
			small_calc = stack->small_heigh - (calc * multi--);
			rotate_based_on_calc(stack, small_calc, 'd');
		}
	}
}

/*	rotation logic for stack b middle numbered section	*/

void	sort_middle(t_stack *stack, int calc, int multi)
{
	int first;
	int mid_calc;

	--multi;
	mid_calc = stack->big_low - (calc * multi--);
	first = TRUE;
	while (multi >= -1)
	{
		push_to_a_or_rotate(stack, first, mid_calc);
		if (first == FALSE && stack->b[stack->bottom - 1] >= stack->big_low)
		{
			mid_calc = stack->big_low - (calc * multi--);
			first = TRUE;
		}
		else if (first == TRUE && stack->b[stack->top_b] >= stack->big_low)
		{
			first = FALSE;
			mid_calc = stack->big_low - (calc * multi--);
			rotate_based_on_calc(stack, mid_calc, 'd');
		}
	}
}

/*	apply same rotation logic to middle and small numbers	*/

void	sort_biggest(t_stack *stack, int calc, int multi)
{
	int	check_nbr;
	int big_calc;

	check_nbr = stack->b[stack->bottom - 1];
	--multi;
	big_calc = stack->big_heigh - (calc * multi--);
	while (stack->b_empty == FALSE)
	{
		if (stack->b[stack->top_b] <= big_calc)
		{
			if (stack->b[stack->top_b] == check_nbr)
				check_nbr = stack->b[stack->top_b + 1];
			push_and_update(stack, 'a');
		}
		else
			rotate_based_on_calc(stack, big_calc, 'r');
		if (stack->b[stack->top_b] == check_nbr)
		{
			big_calc = stack->big_heigh - (calc * multi);
			--multi;
		}
	}
}
