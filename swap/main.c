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
