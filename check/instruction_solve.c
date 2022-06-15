/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:49:06 by molesen           #+#    #+#             */
/*   Updated: 2022/05/09 19:49:08 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/*	checks if instructions are valid	*/

static int	valid_instruction_checker(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (ft_strcmp(line, "sa") == 0 || ft_strcmp(line, "sb") == 0)
		return (0);
	if (ft_strcmp(line, "pa") == 0 || ft_strcmp(line, "pb") == 0)
		return (0);
	if (ft_strcmp(line, "ra") == 0 || ft_strcmp(line, "rb") == 0)
		return (0);
	if (ft_strcmp(line, "rr") == 0 || ft_strcmp(line, "rrr") == 0)
		return (0);
	if (ft_strcmp(line, "rra") == 0 || ft_strcmp(line, "rrb") == 0)
		return (0);
	return (ERROR);
}

/*	reads one line at a time and checks instruction	*/

int	instruction_solve(t_stack *stack)
{
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	while (ret == 1)
	{
		ret = get_next_line(0, &line);
		if (ret == ERROR)
			return (error(stack, 1, line));
		if (!line)
			break ;
		if (valid_instruction_checker(line) == ERROR)
			return (error(stack, 1, line));
		solve_stack(stack, line);
		free(line);
	}
	if (check_if_solved(stack) == ERROR)
		return (1);
	return (0);
}
