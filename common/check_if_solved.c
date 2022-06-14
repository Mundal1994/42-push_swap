/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_solved.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:24:02 by molesen           #+#    #+#             */
/*   Updated: 2022/05/12 18:24:04 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*	error printing message	*/

int	error(t_stack *stack, int i)
{
	if (i == 1)
	{
		if (stack->a)
			free(stack->a);
		if (stack->b)
			free(stack->b);
	}
	free(stack);
	ft_putstr_fd("Error\n", 2);
	return (ERROR);
}

/*	checks if stack a has been solved and if stack b is empty	*/

int	check_if_solved(t_stack *stack)
{
	int	i;

	if (stack->b_empty == FALSE)
		return (ERROR);
	i = stack->top_a + 1;
	while (i < stack->bottom)
	{
		if (stack->a[i] < stack->a[i - 1])
			return (ERROR);
		++i;
	}
	return (0);
}
