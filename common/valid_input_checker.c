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

int	error(t_stack *stack)
{
	free(stack);
	ft_putstr_fd("Error\n", 2);
	return (ERROR);
}

/*	checks if integer is bigger than an int	*/

static int	bigger_than_int(char *argv, t_stack *stack, int len)
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
				return (error(stack));
			else if (argv[i] != '-' && nbr_len >= 10 && ft_strncmp(&argv[i], "2147483647", nbr_len) > 0)
				return (error(stack));
			i += nbr_len + 1;
			nbr_len = ft_strlen_stop(&argv[i], ' ');
		}
	}
	else
	{
		if (argv[0] == '-' && len >= 11 && ft_strcmp(argv, "-2147483648") > 0)
			return (error(stack));
		else if (argv[0] != '-' && len >= 10 && ft_strcmp(argv, "2147483647") > 0)
			return (error(stack));
	}
	return (0);
}

/*	checks if there are any duplicate digits	*/

static int	duplicates_checker(int argc, char **argv, t_stack *stack, int i)
{
	int	begin;
	int	count;
	int	j;
	int	len;

	begin = i;
	len = ft_strlen_stop(argv[begin], ' ');
	if (ft_memchr(argv[begin], ' ', ft_strlen(argv[begin])) != NULL)
	{
		ft_putstr("hello");
		count = ft_word_count(argv[i], ' ');
		j = len;
		while (i < argc)
		{
			while (j < count)
			{
				if (len == ft_strlen_stop(&argv[begin][j], ' '))
					if (ft_strncmp(argv[begin], argv[i], len) == 0)
						return (error(stack));
				++j;
			}
			j += ft_strlen_stop(&argv[begin][j], ' ');
			++i;
		}
	}
	else
	{
		while (++i < argc)
		{
			ft_putstr("hello11");
			if (ft_memchr(argv[i], ' ', ft_strlen(argv[i])) != NULL)
			{
				count = ft_word_count(argv[i], ' ');
				j = 0;
				while (j < count)
				{
					if (len == ft_strlen_stop(argv[i], ' '))
						if (ft_strncmp(argv[begin], argv[i], len) == 0)
							return (error(stack));
					++j;
				}
			}
			if (ft_strcmp(argv[begin], argv[i]) == 0)
				return (error(stack));
		}
	}
	return (0);
}

/*	checks if it is only digits	*/

static int	digit_checker(char *argv, t_stack *stack, int len)
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
			return (error(stack));
	}
	return (0);
}

/*	loops through arguments to check if valid input	*/

int	valid_input_checker(int argc, char **argv, t_stack *stack)
{
	int	i;
	int	len;

	i = 1;
	while (i < argc)
	{
		len = ft_strlen(argv[i]);
		if (digit_checker(argv[i], stack, len) == ERROR)
			return (ERROR);
		if (bigger_than_int(argv[i], stack, len) == ERROR)
			return (ERROR);
		if (duplicates_checker(argc, argv, stack, i) == ERROR)
			return (ERROR);
		++i;
	}
	return (0);
}
