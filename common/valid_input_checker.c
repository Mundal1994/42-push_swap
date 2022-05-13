/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:00:57 by molesen           #+#    #+#             */
/*   Updated: 2022/05/09 19:50:08 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*	checks if integer is bigger than an int	*/

static int	bigger_than_int(char *argv, int len)
{
	int	nbr_len;
	int	i;

	nbr_len = ft_strlen_stop(argv, ' ');
	if (nbr_len != len)
	{
		i = 0;
		while (i < len)
		{
			if (argv[i] == '-' && nbr_len >= 11 && ft_strncmp(&argv[i], "-2147483648", nbr_len) > 0)
				return (ERROR);
			else if (argv[i] != '-' && nbr_len >= 10 && ft_strncmp(&argv[i], "2147483647", nbr_len) > 0)
				return (ERROR);
			i += nbr_len + 1;
			nbr_len = ft_strlen_stop(&argv[i], ' ');
		}
	}
	else
	{
		if (argv[0] == '-' && len >= 11 && ft_strcmp(argv, "-2147483648") > 0)
			return (ERROR);
		else if (argv[0] != '-' && len >= 10 && ft_strcmp(argv, "2147483647") > 0)
			return (ERROR);
	}
	return (0);
}

/*	checks if it is only digits	*/

static int	digit_checker(char *argv, int len)
{
	int	j;

	j = 0;
	if (j == 0 && argv[j] == '-' && ft_isdigit(argv[j + 1]) == 1)
		++j;
	while (j < len)
	{
		if (ft_isdigit(argv[j]) == 1)
			++j;
		else if (argv[j] == ' ' && (ft_isdigit(argv[j + 1]) == 1 || argv[j + 1] == '-'))
			++j;
		else if (argv[j] == '-' && ft_isdigit(argv[j + 1]) == 1)
			++j;
		else
			return (ERROR);
	}
	return (0);
}

/*	loops through arguments to check if valid input	*/

int	valid_input_checker(int argc, char **argv, t_stack *stack)
{
	int	i;
	int	len;

	i = 1;
	stack->bottom = 0;
	while (i < argc)
	{
		if (argc)
			stack->bottom += ft_word_count(argv[i], ' ');
		len = ft_strlen(argv[i]);
		if (digit_checker(argv[i], len) == ERROR)
			return (error(stack, 0));
		if (bigger_than_int(argv[i], len) == ERROR)
			return (error(stack, 0));
		++i;
	}
	stack->top_a = 0;
	stack->top_b = stack->bottom;
	stack->a_empty = FALSE;
	stack->b_empty = TRUE;
	return (0);
}
