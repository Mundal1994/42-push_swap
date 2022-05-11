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

void	*create_stack(int argc, char **argv, t_stack *stack)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	stack = malloc(sizeof(t_stack));
	if (!stack)
		exit(1);
	stack->a = (int *)malloc(sizeof(int) * (argc - 1));
	stack->b = (int *)malloc(sizeof(int) * (argc - 1));
	if (!stack->a || !stack->b)
		exit(1);
	while (i < argc)
	{
		stack->a[j] = (int)malloc(sizeof(int));
		stack->b[j] = (int)malloc(sizeof(int));
		if (!stack->a[j] || !stack->b)
			exit(1);
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
	return (stack);
	/*i = 1;
	j = 0;
	int nbr;
	nbr = argc / 2;
	if (argc % 2 > 0)
		nbr += 1;*/
	// need to use this number to create malloc for stack b
}


/*

stack sorting logic

collect middle number aka argc / 2

while loop

1. check if stack a is sorted
2. check if stack b is sorted
3. check first two elements of stack a
	if below middle number or equal to then move to stack b if following conditions are meet
		the next number in the stack isn't the closest above number with the one we are comparing to
		(ex if we look at 2 but the one below it is 3 then it is sorted correctly)
	
4. 
5. 
6. 


*/