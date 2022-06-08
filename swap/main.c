/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:50:20 by molesen           #+#    #+#             */
/*   Updated: 2022/05/09 19:50:21 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	data_collect(t_stack *stack)
{
	int	i;
	int	j;
	int	count;

	stack->mid_low = -2147483648;
	stack->mid_heigh = -2147483648;
	stack->small_low = 2147483647;
	stack->small_heigh = 2147483647;
	stack->big_low = -2147483648;
	stack->big_heigh = -2147483648;
	i = 0;
	while (i < stack->bottom)
	{
		j = 0;
		count = 0;
		while (j < stack->bottom)
		{
			if (stack->a[j] < stack->a[i])
				++count;
			++j;
		}
		if (count == (stack->bottom / 3) * 1)
			stack->mid_low = stack->a[i];
		else if (count == ((stack->bottom / 3) * 1) - 1)
			stack->small_heigh = stack->a[i];
		else if (count == 0)
			stack->small_low = stack->a[i];
		else if (count == stack->bottom - 1)
			stack->big_heigh = stack->a[i];
		else if (count == ((stack->bottom / 3) * 2) + 1)
			stack->big_low = stack->a[i];
		else if (count == (stack->bottom / 3) * 2)
			stack->mid_heigh = stack->a[i];
		++i;
	}
	//ft_printf("small_low: %d	small_heigh: %d\nmid_low: %d	mid_heigh: %d\nbig_low: %d	big_heigh: %d\n", stack->small_low, stack->small_heigh, stack->mid_low, stack->mid_heigh, stack->big_low, stack->big_heigh);
}

int	main(int argc, char **argv)
{
	t_stack	*stack;

	if (argc > 1)
	{
		stack = malloc(sizeof(t_stack));
		if (!stack)
			exit(1);
		if (valid_input_checker(argc, argv, stack) == ERROR)
			return (1);
		if (create_stack(argc, argv, stack) == ERROR)
			return (1);
		data_collect(stack);
		sort_stack(stack);
		if (stack->a)
			free(stack->a);
		if (stack->b)
			free(stack->b);
		if (stack)
			free(stack);
		/*
			maybe sort into two stacks... i move everything from one stack to the other wait.... i can only move top element...
			would be nice if i could get all the lower numbers to stack b and then sort them in opposet of ascending order that way it is easy to add them to stack a
			or maybe move big numbers to stack b and switch the order and move correct order to stack a if we have a lot of numbers? but that might also be a lot of movig back and forward??
		*/


		/*
			check what number has argc / 2 amount of numbers below it
			we then keep either switching the two things in the beginning of the string
			OR
			if it is below that number we located in the beginning we move it to stack b

			as stack b will get filled up it will go through same process as stack a.
			keep rotating what is on top and keep switching position of numbers until everything is sorted in ascending order in stack a
			stack be will be sorted in descending order.

			when both are sorted we move everything from b to a
		*/
	}
	else
		ft_putstr_fd("Usage: ./push_swap nbr1 nbr2 ...\n", 1);
	return (0);
}
