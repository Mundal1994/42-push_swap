/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:49:24 by molesen           #+#    #+#             */
/*   Updated: 2022/05/09 19:49:25 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int main(int argc, char **argv)
{
	char	*line;

	line = NULL;
	if (argc > 1)
	{
		if (valid_input_checker(argc, argv) == ERROR)
			return (1);
		// while stack hasn't been solved or cannot be solved
		while (1)
		{
			if (get_next_line(0, &line) == ERROR)
			{
				if (line)
					free(line);
				ft_putstr_fd("Error\n", 2);
				return (1);
			}
			if (valid_instruction_checker(line) == ERROR)
				return (1);
			//save all of the instructions into an array so we can follow them afterwards to try and chekc if they are working
			//ft_printf("line: %s\n", line);
			free(line);
		}
		// after collecting everything we need to create stack a and b
		// a if going to collect all the numbers from argv. first argv needs to be at the top of the stack
		// b is going to be empty
		// try to solve based on the input given from the push_swap or terminal
			// check if b is empty after last command has been given
			// check if a is sorted in ascending order
			// or else failed
	}
	else
		ft_putstr_fd("Usage: ./checker nbr1 nbr2 ...\n", 1);
	return (0);
}
