/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:51:34 by molesen           #+#    #+#             */
/*   Updated: 2022/05/10 16:51:36 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	check_if_solved(t_stack *stack, char c)
{
	int	i;

	if (stack->b_empty == FALSE)
	{
		if (c == 'c')
			ft_putstr("KO\n");
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

void	create_stack(int argc, char **argv, t_stack *stack)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	stack->a = (int *)malloc(sizeof(int) * (argc - 1));
	stack->b = (int *)malloc(sizeof(int) * (argc - 1));
	if (!stack->a || !stack->b)
		exit(1);
	while (i < argc)
	{
		stack->a[j] = ft_atoi(argv[i]);
		stack->b[j] = 0;
		++j;
		++i;
	}
	stack->top_a = 0;
	stack->top_b = j;
	stack->bottom = j;
	stack->a_empty = FALSE;
	stack->b_empty = TRUE;
}
