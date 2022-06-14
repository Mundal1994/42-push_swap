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
			if (argv[i] == '-' && nbr_len >= 11)
			{
				if (nbr_len > 11 || (nbr_len == 11 && ft_strncmp(&argv[i], "-2147483648", nbr_len) > 0))
					return (ERROR);
			}
			else if (argv[i] != '-' && nbr_len >= 10)
				if (nbr_len > 10 || (nbr_len == 10 && ft_strncmp(&argv[i], "2147483647", nbr_len) < 0))
					return (ERROR);
			i += nbr_len + 1;
			nbr_len = ft_strlen_stop(&argv[i], ' ');
		}
	}
	else
	{
		ft_printf("len: %d, strcmp: %d\n", len, ft_strcmp(argv, "2147483647"));
		if (argv[0] == '-' && len >= 11)
		{
			if (len > 11 || (len == 11 && ft_strcmp(argv, "-2147483648") > 0))
				return (ERROR);
		}
		else if (argv[0] != '-' && len >= 10)
			if (len > 10|| (len == 10 && ft_strcmp(argv, "2147483647") > 0))
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

/*	loops through arguments to check if valid input	*/

int	valid_input_checker(int argc, char **argv, t_stack *stack)
{
	int	i;
	int	len;

	i = 1;
	if (stack->visual == TRUE)
		++i;
	stack->bottom = 0;
	while (i < argc)
	{
		stack->line = argv[i];
		if (ft_isdigit(stack->line[0]) == 0 && ft_isdigit(stack->line[1]) == 0)
			read_from_file(stack);
		if (argc)
			stack->bottom += ft_word_count(stack->line, ' ');
		len = ft_strlen(stack->line);
		if (digit_checker(stack->line, len) == ERROR)
			return (error(stack, 0));
		if (bigger_than_int(stack->line, len) == ERROR)
			return (error(stack, 0));
		++i;
	}
	stack->top_a = 0;
	stack->top_b = stack->bottom;
	stack->a_empty = FALSE;
	stack->b_empty = TRUE;
	return (0);
}
