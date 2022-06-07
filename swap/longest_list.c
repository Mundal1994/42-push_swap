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

/*	fills array based on how many previous small numbers a number is connected to	*/

static void	*fill_arr(t_stack *stack, int arr[stack->bottom])
{
	int	i;
	int	j;

	i = 0;
	stack->len = 0;
	stack->ordered_big = stack->a[i];
	while (i < stack->bottom)
	{
		j = 0;
		while (j < i)
		{
			if (stack->a[j] < stack->a[i] && arr[j] >= arr[i])
			{
				arr[i] += 1;
				if (stack->len < arr[i])
				{
					stack->len = arr[i];
					stack->ordered_big = stack->a[i];
				}
			}
			++j;
		}
		++i;
	}
	return (arr);
}

static void	*fill_arr_stack_b(t_stack *stack, int arr[stack->bottom])
{
	int	i;
	int	j;

	i = stack->top_b;
	stack->len = 0;
	stack->b_big = stack->b[i];
	while (i < stack->bottom)
	{
		if (stack->b_big < stack->b[i])
			stack->b_big = stack->b[i];
		j = stack->top_b;
		while (j < i)
		{
			if (stack->b[j] > stack->b[i] && arr[j] >= arr[i])
			{
				arr[i] += 1;
				if (stack->len < arr[i])
				{
					stack->len = arr[i];
					//stack->b_big = stack->b[i];
				}
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

static void	collect_list_stack_b(t_stack *stack, int arr[stack->bottom], int k, int i)
{
	while (i < stack->bottom)
	{
		if (k == 0)
		{
			if (arr[i] == arr[k])
			{
				stack->list[k] = stack->b[i];
				collect_list_stack_b(stack, arr, k + 1, i + 1);
			}
		}
		else if (stack->b[i] < stack->list[k - 1] && arr[i] == k + 1)
		{
			stack->list[k] = stack->b[i];
			collect_list_stack_b(stack, arr, k + 1, i + 1);
		}
		++i;
		if (stack->list[stack->len - 1] != -2147483648)
			break ;
	}
}

/*	collects the longest list of already sorted numbers	*/

/*

think i need to fix collection of list of stack b

*/

int	longest_list(t_stack *stack, char c)
{
	int	arr[stack->bottom];
	int	i;

	i = 0;
	while (i < stack->bottom)
	{
		arr[i] = 1;
		++i;
	}
	if (c == 'a')
		fill_arr(stack, arr);
	else
		fill_arr_stack_b(stack, arr);
	if (stack->list)
		free(stack->list);
	if (stack->len > 0)
	{
		stack->list = (int *)malloc(sizeof(int) * stack->len);
		if (!stack->list)
			return (-1);
		i = 0;
		while (i < stack->len)
		{
			stack->list[i] = -2147483648;
			++i;
		}
		if (c == 'a')
		{
			collect_list(stack, arr, 0, 0);
			stack->ordered_small = stack->list[0];
		}
		else
		{
			collect_list_stack_b(stack, arr, 0, 0);
			stack->b_small = stack->list[0];
		}
	}
	return (stack->len);
}
