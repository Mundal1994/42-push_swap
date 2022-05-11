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

static int	rotate_check(char *line, int len)
{
	switch(line[1])
	{
		case 'a':
		case 'b':
			return (0);
		case 'r':
			if (len == 2)
				return (0);
			switch(line[2])
			{
				case 'a':
				case 'b':
				case 'r':
					if (len == 3)
						return (0);
					return (ERROR);
			}
		default:
			return (ERROR);
	}
}

static int	swap_push_check(char *line, int len, char c)
{
	if (c == 's')
	{
		switch(line[1])
		{
			case 'a':
			case 'b':
			case 's':
				if (len == 2)
					return (0);
				return (ERROR);
		}
	}
	else if (c == 'p')
	{
		switch(line[1])
		{
			case 'a':
			case 'b':
				if (len == 2)
					return (0);
				return (ERROR);
		}
	}
	return (ERROR);
}

static int	valid_instruction_checker(char *line)
{
	int	len;

	len = ft_strlen(line);
	switch(line[0])
	{
		case 's':
			if (swap_push_check(line, len, 's') == 0)
				return (0);
			return (error());
		case 'p':
			if (swap_push_check(line, len, 'p') == 0)
				return (0);
			return (error());
		case 'r':
			if (rotate_check(line, len) == 0)
				return (0);
			return (error());
		default:
			return (error());
	}
}

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
		{
			if (line)
				free(line);
			ft_putstr_fd("Error\n", 2);
			return (1);
		}
		if (line == '\0')
			break ;
		if (valid_instruction_checker(line) == ERROR)
			return (1);
		solve_stack(stack, line);
		free(line);
	}
	if (check_if_solved(stack, 'c') == ERROR)
		return (ERROR);
	return (0);
}
