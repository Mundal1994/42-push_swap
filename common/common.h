/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:49:57 by molesen           #+#    #+#             */
/*   Updated: 2022/05/09 19:50:01 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "../libft/ft_printf.h"
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_stack
{
	int			*a;
	int			*b;
	int			top_a;
	int			top_b;
	int			bottom;
	int			a_empty;
	int			b_empty;
	int			a_small;
	int			a_big;
	int			b_small;
	int			b_big;
	int			*list;
	int			len;
	int			small_low;
	int			small_heigh;
	int			big_low;
	int			big_heigh;
	char		*line;
	int			visual;
}	t_stack;

int		valid_input_checker(int argc, char **argv, t_stack *stack);
void	read_from_file(t_stack *stack);
int		error(t_stack *stack, int i, char *line);
void	free_stack(t_stack *stack);
int		check_if_solved(t_stack *stack);
int		create_stack(int argc, char **argv, t_stack *stack);
void	solve_stack(t_stack *stack, char *line);

#endif
