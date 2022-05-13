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

int	check_if_solved(t_stack *stack, char check)
{
	int	i;

	if (check == 'c')
	{
		if (stack->b_empty == ERROR)
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
