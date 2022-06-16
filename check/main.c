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

/*	beginning of checker function. calls nescessary functions	*/

int	main(int argc, char **argv)
{
	t_stack	*stack;
	int		ret;

	if (argc > 1)
	{
		stack = malloc(sizeof(t_stack));
		if (!stack)
			return (0);
		if (valid_input_checker(argc, argv, stack) == ERROR)
			return (0);
		if (create_stack(argc, argv, stack) == ERROR)
			return (0);
		ret = instruction_solve(stack);
		if (ret == ERROR)
			return (0);
		else if (ret == 1)
			ft_putstr("KO\n");
		else
			ft_putstr("OK\n");
		free_stack(stack);
	}
	return (0);
}
