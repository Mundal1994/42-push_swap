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

void	create_stack(int argc, char **argv, t_stack *stack)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	stack = malloc(sizeof(t_stack));
	if (!stack)
		exit(1);
	stack->a = (int *)malloc(sizeof(int) * (argc - 1));
	if (!stack->a)
		exit(1);
	while (i < argc)
	{
		stack->a[j] = (int)malloc(sizeof(int));
		if (!stack->a[j])
			exit(1);
		stack->a[j] = ft_atoi(argv[i]);
		++j;
		++i;
	}
	i = 1;
	j = 0;
	int nbr;
	nbr = argc / 2;
	if (argc % 2 > 0)
		nbr += 1;
	// need to use this number to create malloc for stack b
}


//ASK JEFF
/*
in the int array how to defirenciate between the number 0
and the array having an empty element?

maybe then it is better to use a char array and then just use ft_strcmp?

*/