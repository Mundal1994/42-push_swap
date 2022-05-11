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
	t_stack	*stack;

	if (argc > 1)
	{
		if (valid_input_checker(argc, argv) == ERROR)
			return (1);
		stack = malloc(sizeof(t_stack));
		if (!stack)
			exit(1);
		create_stack(argc, argv, stack);
		if (instruction_solve(stack) == ERROR)
			return (1);
		free(stack);
	}
	else
		ft_putstr_fd("Usage: ./checker nbr1 nbr2 ...\n", 1);
	return (0);
}
