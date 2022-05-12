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

static int	is_stack_empty(int empty, char c)
{
	if (empty == FALSE)
	{
		if (c == 'c')
			ft_putstr("KO\n");
		return (ERROR);
	}
	return (0);
}

int	check_if_solved(t_stack *stack, char c, char check)
{
	int	i;

	if (check == 'c')
	{
		if (is_stack_empty(stack->b_empty, c) == ERROR)
			return (ERROR);
	}
	i = 1;
	while (i < stack->bottom)
	{
		if (stack->a[i] < stack->a[i - 1])
		{
			if (c == 'c')
				ft_putstr("KO\n");
			return (ERROR);
		}
		++i;
	}
	if (c == 'c')
		ft_putstr("OK\n");
	return (0);
}
