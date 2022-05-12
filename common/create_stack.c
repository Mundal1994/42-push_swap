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
/*
static int	arg_string(char **argv, t_stack *stack)
{

	return (i);
}
*/

void	element_counter(int argc, char **argv, t_stack *stack)
{
	int	i;

	i = 1;
	stack->bottom = 0;
	while (i < argc)
	{
		stack->bottom += ft_word_count(argv[i], ' ');
		++i;
	}
}

void	create_stack(int argc, char **argv, t_stack *stack)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	stack->a = (int *)malloc(sizeof(int) * stack->bottom);
	stack->b = (int *)malloc(sizeof(int) * stack->bottom);
	if (!stack->a || !stack->b)
		exit(1);
	//if (argv[i]) // if contains space we want to call another function
	//	arg_string(argc, stack);
	i = 1;
	if (ft_memchr(argv[i], ' ', ft_strlen(argv[i])) != NULL)
	{
		while (i < argc)
		{
			stack->a[j] = ft_atoi(argv[i]);
			stack->b[j] = 0;
			++j;
			++i;
		}
	}
	stack->top_a = 0;
	stack->top_b = j;
	stack->a_empty = FALSE;
	stack->b_empty = TRUE;
}
