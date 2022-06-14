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

static void	data_collect(t_stack *stack)
{
	int	i;
	int	j;
	int	count;

	stack->small_low = 2147483647;
	stack->small_heigh = 2147483647;
	stack->big_low = -2147483648;
	stack->big_heigh = -2147483648;
	i = 0;
	while (i < stack->bottom)
	{
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
		++i;
	}
}

/*

printf("\033[XA"); // Move up X lines;
printf("\033[XB"); // Move down X lines;
printf("\033[XC"); // Move right X column;
printf("\033[XD"); // Move left X column;
printf("\033[2J"); // Clear screen

*/


static void	print_with_commands(t_stack *stack, char *commands, int first)
{
	int	i;

	//i = 0;
	i = stack->bottom - 1;
	ft_printf("\n\33[2K");
	ft_printf("\n\33[2K{purple}COMMAND:{uncolor} %s\n", commands);
	ft_printf("\n\33[2K");
	ft_printf("{purple}STACK A: {uncolor}");
	while (i > 0)//i < stack->bottom)
	{
		//ft_printf("\x1b[2K");
		if (i < stack->top_a || first == TRUE)
			ft_printf("\033[30;40m0	");
		else if (stack->a[i] >= stack->big_low)
			ft_printf("\033[30;41m%d	\033[0m", stack->a[i]);
		else if (stack->a[i] > stack->small_heigh)
			ft_printf("\033[30;42m%d	\033[0m", stack->a[i]);
		else
			ft_printf("\033[30;46m%d	\033[0m", stack->a[i]);
			/*
			if (i < stack->top_a)
				ft_printf("|		|");
			else if (stack->a[i] >= stack->big_low)
				ft_printf("|\033[30;41m	%d	\033[0m|", stack->a[i]);
			else if (stack->a[i] > stack->small_heigh)
				ft_printf("|\033[30;42m	%d	\033[0m|", stack->a[i]);
			else
				ft_printf("|\033[30;46m	%d	\033[0m|", stack->a[i]);
			if (i < stack->top_b)
				ft_printf("		|\n");
			else if (stack->b[i] >= stack->big_low)
				ft_printf("\033[30;41m	%d	\033[0m|\n", stack->b[i]);
			else if (stack->b[i] > stack->small_heigh)
				ft_printf("\033[30;42m	%d	\033[0m|\n", stack->b[i]);
			else
				ft_printf("\033[30;46m	%d	\033[0m|\n", stack->b[i]);*/
		--i;
		ft_printf("|");
	}
	i = stack->bottom - 1;
	ft_printf("\n\33[2K");
	ft_printf("\n\33[2K{purple}STACK B: {uncolor}");
	while (i > 0)//i < stack->bottom)
	{
		if (i < stack->top_b || first == TRUE)
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
	//ft_printf("     {purple}STACK A	     STACK B{uncolor}	     %s\n", commands);
}

void	make_visuals(t_stack *stack, int first, char *command)
{
	int j = 0;
	int	time;
	
	if (first == FALSE)
		ft_printf("\033c");
	ft_printf("\033[%d;%dH", 0, 0);
	print_with_commands(stack, command, first);
	if (stack->bottom < 50)
		time = 200000000;
	else if (stack->bottom < 250)
		time = 35000000;
	else
		time = 75000000;
	while (j < time)
		++j;
}

int	main(int argc, char **argv)
{
	t_stack	*stack;

	if (argc > 1)
	{
		stack = malloc(sizeof(t_stack));
		if (!stack)
			return (1);
		stack->visual = FALSE;
		if (ft_strcmp("-v", argv[1]) == 0)
			stack->visual = TRUE;
		if (valid_input_checker(argc, argv, stack) == ERROR)
			return (1);
		if (create_stack(argc, argv, stack) == ERROR)
			return (1);
		data_collect(stack);
		if (stack->visual == TRUE)
			make_visuals(stack, TRUE, "none");
		sort_stack(stack);
		if (stack->a)
			free(stack->a);
		if (stack->b)
			free(stack->b);
		if (stack)
			free(stack);
	}
	else
		ft_putstr_fd("Usage: ./push_swap nbr1 nbr2 ...\n", 1);
	return (0);
}
