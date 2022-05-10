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

/*	error printing message	*/

int	error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (ERROR);
}

/*	checks if integer is bigger than an int	*/

static int	bigger_than_int(char *argv, int len)
{
	if (argv[0] == '-' && len >= 11 && ft_strcmp(argv, "-2147483648") > 0)
		return (error());
	else if (argv[0] != '-' && len >= 10 && ft_strcmp(argv, "2147483647") > 0)
		return (error());
	return (0);
}

/*	checks if there are any duplicate digits	*/

static int	duplicates_checker(int argc, char **argv, int i)
{
	int	begin;

	begin = i;
	while (++i < argc)
	{
		if (ft_strcmp(argv[begin], argv[i]) == 0)
			return (error());
	}
	return (0);
}

/*	checks if it is only digits	*/

static int	digit_checker(char *argv, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		if (ft_isdigit(argv[j]) == 0)
		{
			if (j == 0 && argv[j] == '-')
				break ;
			else
				return (error());
		}
		++j;
	}
	return (0);
}

/*	loops through arguments to check if valid input	*/

int	valid_input_checker(int argc, char **argv)
{
	int	i;
	int	len;

	i = 1;
	while (i < argc)
	{
		len = ft_strlen(argv[i]);
		if (digit_checker(argv[i], len) == ERROR)
			return (ERROR);
		if (bigger_than_int(argv[i], len) == ERROR)
			return (ERROR);
		if (duplicates_checker(argc, argv, i) == ERROR)
			return (ERROR);
		++i;
	}
	return (0);
}
