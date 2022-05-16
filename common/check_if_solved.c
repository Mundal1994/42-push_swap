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
		free(stack->a);
		free(stack->b);
	}
	free(stack);
	ft_putstr_fd("Error\n", 2);
	return (ERROR);
}

/*	checks individual stack if solved or not	*/

int	is_stack_solved(int *a, int i, int len)
{
	while (i < len)
	{
		if (a[i] > a[i - 1])
			return (ERROR);
		++i;
	}
	return (0);
}

/*
**	checks if stack a has been solved and depending on when the check occurs
**	stack b will be checked if it is empty or not as well
*/

int	check_if_solved(t_stack *stack, char check)
{
	int	i;

	if (check == 'c')
	{
		if (stack->b_empty == FALSE)
			return (ERROR);
	}
	i = 1;
	while (i < stack->bottom)
	{
		if (stack->a[i] < stack->a[i - 1])
			return (ERROR);
		++i;
	}
	return (0);
}
