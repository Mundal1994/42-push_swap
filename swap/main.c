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
	int	i;

	i = 1;
	if (argc > 1)
	{
		if (valid_input_checker(argc, argv) == ERROR)
			return (1);
		// create stack a and b
		// a if going to collect all the numbers from argv. first argv needs to be at the top of the stack
		// b is going to be empty
		//find shortest combo and print to standard output followed by a '\n'
		while (i < argc)
		{
			ft_putstr("sa");
			ft_putchar('\n');
			++i;
		}
		// while stack hasn't been solved or cannot be solved



		/*
			maybe sort into two stacks... i move everything from one stack to the other wait.... i can only move top element...
			would be nice if i could get all the lower numbers to stack b and then sort them in opposet of ascending order that way it is easy to add them to stack a
			or maybe move big numbers to stack b and switch the order and move correct order to stack a if we have a lot of numbers? but that might also be a lot of movig back and forward??
		*/
	}
	else
		ft_putstr_fd("Usage: ./checker nbr1 nbr2 ...\n", 1);
	return (0);
}
