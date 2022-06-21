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

/*	collects heighest and smallest number for big and small sections	*/

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

/*	collects data for big and small sections	*/

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

/*	push_swap main function	*/

int	main(int argc, char **argv)
{
	t_stack	*stack;

	if ((argc > 1 && ft_strcmp("-v", argv[1]) != 0) || (argc > 2 && \
		ft_strcmp("-v", argv[1]) == 0))
	{
		stack = malloc(sizeof(t_stack));
		if (!stack)
			return (0);
		stack->visual = FALSE;
		if (ft_strcmp("-v", argv[1]) == 0)
			make_visuals(stack, TRUE, "none");
		if (valid_input_checker(argc, argv, stack) == ERROR)
			return (0);
		if (create_stack(argc, argv, stack) == ERROR)
			return (0);
		data_collect(stack);
		if (stack->visual == TRUE)
			make_visuals(stack, FALSE, "original stack");
		if (check_if_solved(stack) == ERROR)
			sort_stack(stack);
		free_stack(stack);
	}
	return (0);
}
