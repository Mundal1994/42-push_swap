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

int	main(int argc, char **argv)
{
	t_stack	*stack;
	int		ret;

	if (argc > 1)
	{
		stack = malloc(sizeof(t_stack));
		if (!stack)
			exit(1);
		if (valid_input_checker(argc, argv, stack) == ERROR)
			return (1);
		if (create_stack(argc, argv, stack) == ERROR)
			return (1);
		ret = instruction_solve(stack);
		if (ret == ERROR)
			return (1);
		else if (ret == 1)
			ft_putstr("KO\n");
		else
			ft_putstr("OK\n");
		free_stack(stack);
	}
	else
		ft_putstr_fd("Usage: ./checker nbr1 nbr2 ...\n", 1);
	return (0);
}
