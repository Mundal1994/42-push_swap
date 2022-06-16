/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:35:33 by molesen           #+#    #+#             */
/*   Updated: 2022/06/14 16:35:35 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*	prints the visuals of stack b	*/

static void	print_stack_b(t_stack *stack)
{
	int	i;

	i = stack->bottom - 1;
	ft_printf("\n\n{purple}STACK B: {uncolor}");
	while (i >= 0)
	{
		if (i < stack->top_b)
			ft_printf("\033[30;40m0	");
		else if (stack->b[i] >= stack->big_low)
			ft_printf("\033[30;41m%d	\033[0m", stack->b[i]);
		else if (stack->b[i] > stack->small_heigh)
			ft_printf("\033[30;42m%d	\033[0m", stack->b[i]);
		else
			ft_printf("\033[30;46m%d	\033[0m", stack->b[i]);
		--i;
		ft_printf("|");
	}
	ft_printf("\n\033[0;37m______________________\n");
}

/*	prints the visuals of stack a	*/

static void	print_visuals(t_stack *stack, char *commands)
{
	int	i;

	i = stack->bottom - 1;
	ft_printf("\n{purple}COMMAND:{uncolor} %s\n", commands);
	ft_printf("\n");
	ft_printf("{purple}STACK A: {uncolor}");
	while (i >= 0)
	{
		if (i < stack->top_a)
			ft_printf("\033[30;40m0	");
		else if (stack->a[i] >= stack->big_low)
			ft_printf("\033[30;41m%d	\033[0m", stack->a[i]);
		else if (stack->a[i] > stack->small_heigh)
			ft_printf("\033[30;42m%d	\033[0m", stack->a[i]);
		else
			ft_printf("\033[30;46m%d	\033[0m", stack->a[i]);
		--i;
		ft_printf("|");
	}
	print_stack_b(stack);
}

/*	logic of the visuals and takes care of the delaying of next print	*/

void	make_visuals(t_stack *stack, int first, char *command)
{
	int	j;
	int	time;

	if (first == FALSE)
	{
		ft_printf("\033c");
		print_visuals(stack, command);
		if (stack->bottom < 50)
			time = 200000000;
		else if (stack->bottom < 250)
			time = 20000000;
		else
			time = 0;
		j = 0;
		while (j < time)
			++j;
	}
	else
		stack->visual = TRUE;
}
