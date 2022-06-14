/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:39:11 by molesen           #+#    #+#             */
/*   Updated: 2022/05/11 16:39:13 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*	swap elements	*/

static void	swap(int *a, int *b)
{
	int	c;

	c = *b;
	*b = *a;
	*a = c;
}

/*	push one element from one stack to another	*/

static void	*push(int *a, int *b, t_stack *stack, int i)
{
	*a = *b;
	*b = 0;
	if (i == 0)
	{
		stack->top_a -= 1;
		stack->top_b += 1;
	}
	else
	{
		stack->top_a += 1;
		stack->top_b -= 1;
	}
	if (stack->top_a == stack->bottom)
		stack->a_empty = TRUE;
	else
		stack->a_empty = FALSE;
	if (stack->top_b == stack->bottom)
		stack->b_empty = TRUE;
	else
		stack->b_empty = FALSE;
	return (stack);
}

/*	shift all elements of a stack by 1 element. first element becomes last	*/

static void	rotate(int *a, int top_a, int bottom)
{
	int	first;

	first = a[top_a];
	while (top_a < bottom - 1)
	{
		a[top_a] = a[top_a + 1];
		++top_a;
	}
	a[bottom - 1] = first;
}

/*	shift all elements of a stack by 1 element. last element becomes first	*/

static void	reverse_rotate(int *a, int top_a, int bottom)
{
	int	first;

	--bottom;
	first = a[bottom];
	while (bottom > top_a)
	{
		a[bottom] = a[bottom - 1];
		--bottom;
	}
	a[top_a] = first;
}

/*	solve stack function based on instructions	*/

void	solve_stack(t_stack *stack, char *line)
{
	if (stack->a_empty == FALSE && (ft_strcmp(line, "sa") == 0 || \
		ft_strcmp(line, "ss") == 0))
		swap(&stack->a[stack->top_a], &stack->a[stack->top_a + 1]);
	if (stack->b_empty == FALSE && (ft_strcmp(line, "sb") == 0 || \
		ft_strcmp(line, "ss") == 0))
		swap(&stack->b[stack->top_b], &stack->b[stack->top_b + 1]);
	if (stack->b_empty == FALSE && ft_strcmp(line, "pa") == 0)
		push(&stack->a[stack->top_a - 1], &stack->b[stack->top_b], stack, 0);
	if (stack->a_empty == FALSE && ft_strcmp(line, "pb") == 0)
		push(&stack->b[stack->top_b - 1], &stack->a[stack->top_a], stack, 1);
	if (stack->a_empty == FALSE && (ft_strcmp(line, "ra") == 0 || \
		ft_strcmp(line, "rr") == 0))
		rotate(stack->a, stack->top_a, stack->bottom);
	if (stack->b_empty == FALSE && (ft_strcmp(line, "rb") == 0 || \
		ft_strcmp(line, "rr") == 0))
		rotate(stack->b, stack->top_b, stack->bottom);
	if (stack->a_empty == FALSE && (ft_strcmp(line, "rra") == 0 || \
		ft_strcmp(line, "rrr") == 0))
		reverse_rotate(stack->a, stack->top_a, stack->bottom);
	if (stack->b_empty == FALSE && (ft_strcmp(line, "rrb") == 0 || \
		ft_strcmp(line, "rrr") == 0))
		reverse_rotate(stack->b, stack->top_b, stack->bottom);
}
