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

typedef struct s_stack
{
	int			*a;
	int			*b;
	int			top_a;
	int			top_b;
	int			bottom;
	int			a_empty;
	int			b_empty;
} t_stack;

typedef struct s_instruction
{
	char		*instr;
} t_instruction;

int		valid_input_checker(int argc, char **argv, t_stack *stack);
int		error(t_stack *stack, int i);
int		check_if_solved(t_stack *stack, char check);
int		create_stack(int argc, char **argv, t_stack *stack);
void	solve_stack(t_stack *stack, char *line);

#endif
