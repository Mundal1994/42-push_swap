/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:10:11 by molesen           #+#    #+#             */
/*   Updated: 2022/06/03 12:10:12 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	fills array based on how many previous small numbers a number is
**	connected to
*/

static void	*fill_arr(t_stack *stack, int arr[stack->bottom])
{
	int	i;
	int	j;

	i = stack->top_a;
	stack->len = 0;
	while (i < stack->bottom)
	{
		j = stack->top_a;
		while (j < i)
		{
			if (stack->a[j] < stack->a[i] && arr[j] >= arr[i])
			{
				arr[i] += 1;
				if (stack->len < arr[i])
					stack->len = arr[i];
			}
			++j;
		}
		++i;
	}
	return (arr);
}

/*	collect the list of the numbers that are in the longest sorted order	*/

static void	collect_list(t_stack *stack, int arr[stack->bottom], int k, int i)
{
	while (i < stack->bottom)
	{
		if (k == 0)
		{
			if (arr[i] == arr[k])
			{
				stack->list[k] = stack->a[i];
				collect_list(stack, arr, k + 1, i + 1);
			}
		}
		else if (stack->a[i] > stack->list[k - 1] && arr[i] == k + 1)
		{
			stack->list[k] = stack->a[i];
			collect_list(stack, arr, k + 1, i + 1);
		}
		++i;
		if (stack->list[stack->len - 1] != -2147483648)
			break ;
	}
}

/*	initializes longest list	*/

static int	initialize_list(t_stack *stack, int *arr)
{
	int	i;

	if (stack->len > 0)
	{
		stack->list = (int *)malloc(sizeof(int) * stack->len);
		if (!stack->list)
			return (ERROR);
		i = 0;
		while (i < stack->len)
		{
			stack->list[i] = -2147483648;
			++i;
		}
		collect_list(stack, arr, 0, stack->top_a);
	}
	return (0);
}

/*	collects the longest list of already sorted numbers	*/

int	longest_list(t_stack *stack)
{
	int	*arr;
	int	i;

	i = 0;
	arr = (int *)malloc(sizeof(int) * stack->bottom);
	if (!arr)
		return (ERROR);
	while (i < stack->bottom)
	{
		arr[i] = 1;
		++i;
	}
	fill_arr(stack, arr);
	if (initialize_list(stack, arr) == ERROR)
	{
		free(arr);
		return (ERROR);
	}
	free(arr);
	return (stack->len);
}
