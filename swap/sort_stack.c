
#include "push_swap.h"

static void	divide_calculater(t_stack *stack, int *divider)
{
	int	below;
	int	nbr;
	int	i;
	int	j;
	int	count;

	if (stack->bottom < 4)
		below = -2147483648;
	else if (stack->bottom < 50)
		below = stack->bottom - (stack->bottom / 3);
	else
		below = stack->bottom - (stack->bottom / 4);
	i = 0;
	while (*divider == -2147483648 && below != -2147483648 && i < stack->bottom)
	{
		nbr = stack->a[i];
		j = 0;
		count = 0;
		while (j < stack->bottom && nbr != -2147483648)
		{
			if (stack->a[j] < nbr)
				++count;
			++j;
		}
		if (count >= below && count <= stack->bottom)
			*divider = nbr;
		++i;
	}
}

//function that lets me know if the element belov is either heigher or lower
// than current number. 
// function that return 1 if the number below is the number closests to current number because if it is we don't want to put in to stack b

static int	ordered(int *a, int *b, int top, int bottom)
{
	int	nbr;
	int	orig;

	orig = a[0];
	nbr = a[1];
	top += 2;
	if (orig > nbr)
	{
		while (top < bottom)
		{/*
			ft_putstr("orig: ");
	ft_putnbr(orig);
			ft_putchar('\n');
			ft_putstr("nbr: ");
			ft_putnbr(nbr);
			ft_putchar('\n');
			ft_putnbr(b[top]);
			ft_putchar('\n');*/
			if (b[top] > nbr && b[top] < orig)
				return (FALSE);
			++top;
		}
	}
	else
	{
		while (top < bottom)
		{
			if (b[top] < nbr && b[top] > orig)
				return (FALSE);
			++top;
		}
	}
	return (TRUE);
}

void	sort_stack(t_stack *stack)
{
	int	divider;

	divider = -2147483648;
	divide_calculater(stack, &divider);
	while (check_if_solved(stack, 'c') == ERROR)
	{
		//make a check for if b is in order
		
		if (stack->a_empty == FALSE && stack->a[stack->top_a] > stack->a[stack->top_a + 1])
		{
			if (stack->b_empty == FALSE && stack->b[stack->top_b] < stack->b[stack->top_b + 1])
			{
				solve_stack(stack, "ss");
				ft_putstr("ss");
			}
			else
			{
				solve_stack(stack, "sa");
				ft_putstr("sa");
			}
		}
		else if (stack->b_empty == FALSE && stack->b[stack->top_b] < stack->b[stack->top_b + 1])
		{
			solve_stack(stack, "sb");
			ft_putstr("sb");
		}
		else if (stack->b_empty == FALSE && ordered(&stack->b[stack->top_b], stack->a, stack->top_a - 2, stack->bottom) == TRUE && check_if_solved(stack, 'p') == 0)
		{
			solve_stack(stack, "pa");
			ft_putstr("pa");
		}
		else if (stack->a_empty == FALSE && stack->a[stack->top_a] < divider && ordered(&stack->a[stack->top_a], stack->a, stack->top_a, stack->bottom) == FALSE && check_if_solved(stack, 'p') == ERROR)
		{
			// if a is in order we need to stop this one and start pushing from b to a
			solve_stack(stack, "pb");
			ft_putstr("pb");
		}
		ft_putchar('\n');
	}
}

/*

rust is a good language to learn

i = 1;
	j = 0;
	int nbr;
	nbr = argc / 2;
	if (argc % 2 > 0)
		nbr += 1;
	 need to use this number to create malloc for stack b

stack sorting logic

collect middle number aka argc / 2

while loop

1. check if stack a is sorted
	if sorted check if b is empty
2. check if stack b is sorted
3. check first two elements of stack a
	if below middle number(try with 1/4) or equal to then move to stack b if following conditions are meet
		the next number in the stack isn't the closest above number with the one we are comparing to
		(ex if we look at 2 but the one below it is 3 then it is sorted correctly - so dont move to stack b if a is sorted or maybe more check if there is one difference)
4. switch top if wrong order (do with both stacks)
5. rotate one way depending on where the next closest to middle number is (check is stack b also should rotate)
6. 

*/