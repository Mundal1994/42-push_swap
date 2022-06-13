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
		if (count == ((stack->bottom / 3) * 1) - 1)
			stack->small_heigh = stack->a[i];
		else if (count == 0)
			stack->small_low = stack->a[i];
		else if (count == stack->bottom - 1)
			stack->big_heigh = stack->a[i];
		else if (count == ((stack->bottom / 3) * 2) + 1)
			stack->big_low = stack->a[i];
		++i;
	}
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
	}
	else
		ft_putstr_fd("Usage: ./push_swap nbr1 nbr2 ...\n", 1);
	return (0);
}
