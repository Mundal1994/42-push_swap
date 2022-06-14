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
	if (stack->a_small > stack->a_big)
	{
		stack->a_small = stack->a[0];
		stack->a_big = stack->a[0];
	}
	else if (stack->a[j] < stack->a_small)
		stack->a_small = stack->a[j];
	else if (stack->a[j] > stack->a_big)
		stack->a_big = stack->a[j];
	while (i < j)
	{
		if (stack->a[i] == stack->a[j])
			return (ERROR);
		++i;
	}
	return (0);
}

/*	collecting digits from a string while loop	*/

static int	collect_from_str(char *line, t_stack *stack, int *j)
{
	int	k;
	int	len;

	k = 0;
	len = ft_strlen(line);
	while (k < len)
	{
		stack->a[*j] = ft_atoi(&line[k]);
		stack->b[*j] = 0;
		if (duplicates_checker(stack, *j) == ERROR)
			return (ERROR);
		k += ft_strlen_stop(&line[k], ' ') + 1;
		++(*j);
	}
	return (0);
}

/*	initializes stacks with numbered arguments	*/

static int	initialize_stacks(char **argv, t_stack *stack, int i, int *j)
{
	if (ft_memchr(argv[i], ' ', ft_strlen(argv[i])) != NULL)
	{
		if (collect_from_str(argv[i], stack, j) == ERROR)
			return (ERROR);
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

/*	initializes stack if it is read from a file	*/

static int	initialize_stack_file(char *line, t_stack *stack, int *j)
{
	if (collect_from_str(line, stack, j) == ERROR)
	{
		free(stack->line);
		return (ERROR);
	}
	free(stack->line);
	return (0);
}

/*	mallocs and starts creatings stack a and b	*/

// maybe free stack->a or stack->b

int	create_stack(int argc, char **argv, t_stack *stack)
{
	int	i;
	int	j;

	stack->a = (int *)malloc(sizeof(int) * stack->bottom);
	stack->b = (int *)malloc(sizeof(int) * stack->bottom);
	if (!stack->a || !stack->b)
		return (error(stack, 1));
	i = 1;
	if (stack->visual == TRUE)
		++i;
	j = 0;
	stack->a_small = 1;
	stack->a_big = -1;
	if (ft_isdigit(argv[i][0]) == 0 && ft_isdigit(argv[i][1]) == 0)
	{
		if (initialize_stack_file(stack->line, stack, &j) == ERROR)
			return (error(stack, 1));
	}
	else
	{
		while (i < argc)
		{
			if (initialize_stacks(argv, stack, i, &j) == ERROR)
				return (error(stack, 1));
			++i;
		}
	}
	stack->b_small = 2147483647;
	stack->b_big = -2147483648;
	return (0);
}
