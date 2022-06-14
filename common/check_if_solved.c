/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_solved.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:24:02 by molesen           #+#    #+#             */
/*   Updated: 2022/05/12 18:24:04 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*	reads numbers from file	*/

void	read_from_file(t_stack *stack)
{
	int		fd;
	int		ret;
	int		ret2;
	char	*temp;

	fd = open(stack->line, O_RDONLY);
	temp = NULL;
	ret = get_next_line(fd, &stack->line);
	ret2 = get_next_line(fd, &temp);
	if (ret != 1 || ret2 != 0)
	{
		stack->line[0] = 'n';
		if (ret2 == 1)
			free(temp);
		close(fd);
	}
	close(fd);
}

/*	frees stack	*/

void	free_stack(t_stack *stack)
{
	if (stack->a)
		free(stack->a);
	if (stack->b)
		free(stack->b);
	if (stack)
		free(stack);
}

/*	error printing message	*/

int	error(t_stack *stack, int i, char *line)
{
	if (line)
		free(line);
	if (i == 1)
	{
		if (stack->a)
			free(stack->a);
		if (stack->b)
			free(stack->b);
	}
	free(stack);
	ft_putstr_fd("Error\n", 2);
	return (ERROR);
}

/*	checks if stack a has been solved and if stack b is empty	*/

int	check_if_solved(t_stack *stack)
{
	int	i;

	if (stack->b_empty == FALSE)
		return (ERROR);
	i = stack->top_a + 1;
	while (i < stack->bottom)
	{
		if (stack->a[i] < stack->a[i - 1])
			return (ERROR);
		++i;
	}
	return (0);
}
