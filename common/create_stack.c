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

/*	checks if there are any duplicate digits	*/

static int	duplicates_checker(t_stack *stack, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		if (stack->a[i] == stack->a[j])
			return (ERROR);
		++i;
	}
	return (0);
}

/*	initializes stacks with numbered arguments	*/

static int	initialize_stacks(char **argv, t_stack *stack, int i, int *j)
{
	int	k;

	if (ft_memchr(argv[i], ' ', ft_strlen(argv[i])) != NULL)
	{
		k = 0;
		while (k < (int)ft_strlen(argv[i]))
		{
			stack->a[*j] = ft_atoi(&argv[i][k]);
			stack->b[*j] = 0;
			if (duplicates_checker(stack, *j) == ERROR)
				return (ERROR);
			k += ft_strlen_stop(&argv[i][k], ' ') + 1;
			++(*j);
		}
	}
	else
	{
		stack->a[*j] = ft_atoi(argv[i]);
		stack->b[*j] = 0;
		if (duplicates_checker(stack, *j) == ERROR)
			return (ERROR);
		++(*j);
	}
	return (0);
}

/*	mallocs and starts creatings stack a and b	*/

int	create_stack(int argc, char **argv, t_stack *stack)
{
	int	i;
	int	j;

	stack->a = (int *)malloc(sizeof(int) * stack->bottom);
	stack->b = (int *)malloc(sizeof(int) * stack->bottom);
	if (!stack->a || !stack->b)
		exit(1);
	i = 1;
	j = 0;
	while (i < argc)
	{
		if (initialize_stacks(argv, stack, i, &j) == ERROR)
			return (error(stack, 1));
		++i;
	}
	return (0);
}
