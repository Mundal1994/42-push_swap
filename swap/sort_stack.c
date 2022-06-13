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

static int	is_sorted(t_stack *stack)
{
	int i = stack->top_a;

	while (i < stack->bottom)
	{
		//if (stack->a[i] <= stack->small_heigh || stack->a[i] >= stack->big_low)
		if (stack->a[i] > stack->small_heigh && is_list(stack, stack->a[i]) < 0)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

static void	sort_smallest(t_stack *stack, int calc, int multi)
{
	int	first;
	int small_calc;

	--multi;
	small_calc = stack->small_heigh - (calc * multi--);
	first = TRUE;
	while (multi >= -1)
	{
		if (first == TRUE && stack->b[stack->top_b] <= small_calc)
			push_and_update(stack, 'a');
		else if (first == TRUE)
			rotate_based_on_calc(stack, small_calc, 'r');
		else if (first == FALSE && stack->b[stack->top_b] <= small_calc)
			push_and_update(stack, 'a');
		else if (first == FALSE)
			rotate_based_on_calc(stack, small_calc, 'd');
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
	/*
	int	check_nbr;
	int small_calc;

	check_nbr = 0;
	--multi;
	small_calc = stack->small_heigh - (calc * multi--);
	while (stack->b_empty == FALSE)
	{
		if (stack->b[stack->top_b] <= small_calc)
		{
			if (stack->b[stack->top_b] == check_nbr)
				check_nbr = stack->b[stack->top_b + 1];
			push_and_update(stack, 'a');
		}
		else
		{
			if (!check_nbr)
				check_nbr = stack->b[stack->top_b];
			rotate_based_on_calc(stack, small_calc, 'r');
		}
		if (stack->b[stack->top_b] == check_nbr)
		{
			small_calc = stack->small_heigh - (calc * multi);
			--multi;
		}
	}*/
}

void	sort_stack(t_stack *stack)
{
	if (check_if_solved(stack) == ERROR)
	{
		longest_list(stack);
		while (is_sorted(stack) == FALSE)
		{
			//if (stack->a[stack->top_a] <= stack->small_heigh)
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
		if (stack->list)
			free(stack->list);
		int multi;
		
		if (stack->bottom < 50)
			multi = 2;
		if (stack->bottom < 250)
			multi = 6;
		else
			multi = 10;
		sort_smallest(stack, (stack->small_heigh - stack->small_low) / multi, multi);
		sort_middle(stack, (stack->big_low - stack->small_heigh) / multi, multi);
		sort_biggest(stack, (stack->big_heigh - stack->big_low) / multi, multi);
		stack_rotate_init(stack);
	}
}



/*

look at how algorythm is working.

something wrong with pushing to stack a were it loops way to much.
maybe figure out a better way to sort stack b than pushing directly to stack a


is there a way to sort as many of the chunks as i'm pushing to stack b to make sure i can get a bigger chunk in stack b that is going to be in order??

*/



/*

rust is a good language to learn

*/
