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

static void	data_of_big_and_small(t_stack *stack, int i)
{
	int	j;
	int	count;

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
}

static void	data_collect(t_stack *stack)
{
	int	i;

	stack->small_low = stack->a_small;
	stack->small_heigh = stack->a_small;
	stack->big_low = stack->a_big;
	stack->big_heigh = stack->a_big;
	i = 0;
	while (i < stack->bottom)
	{
		data_of_big_and_small(stack, i);
		++i;
	}
}

int	main(int argc, char **argv)
{
	t_stack	*stack;

	if ((argc > 1 && ft_strcmp("-v", argv[1]) != 0) || (argc > 2 &&\
		ft_strcmp("-v", argv[1]) == 0))
	{
		stack = malloc(sizeof(t_stack));
		if (!stack)
			return (1);
		stack->visual = FALSE;
		if (ft_strcmp("-v", argv[1]) == 0)
			make_visuals(stack, TRUE, "none");
		if (valid_input_checker(argc, argv, stack) == ERROR)
			return (1);
		if (create_stack(argc, argv, stack) == ERROR)
			return (1);
		data_collect(stack);
		if (stack->visual == TRUE)
			make_visuals(stack, FALSE, "original stack");
		sort_stack(stack);
		free_stack(stack);
	}
	else
		ft_putstr_fd("Usage: ./push_swap nbr1 nbr2 ...\n", 1);
	return (0);
}
