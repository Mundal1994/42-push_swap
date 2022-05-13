
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
/*
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
		{
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
*/
void	sort_stack(t_stack *stack)
{
	int	divider;

	divider = -2147483648;
	divide_calculater(stack, &divider);
	int i = 0;
	while (i++ < 10 && check_if_solved(stack, 'c') == ERROR)
	{
		//make a check for if b is in order
		if (stack->b_empty == FALSE && check_if_solved(stack, 'p') == 0)//ordered(&stack->b[stack->top_b], stack->a, stack->top_a - 2, stack->bottom) == TRUE
		{
			solve_stack(stack, "pa");
			ft_putstr("pa\n");
		}
		else if (stack->a_empty == FALSE && stack->a[stack->top_a] < divider && check_if_solved(stack, 'p') == ERROR)//ordered(&stack->a[stack->top_a], stack->a, stack->top_a, stack->bottom) == FALSE
		{
			// if a is in order we need to stop this one and start pushing from b to a
			solve_stack(stack, "pb");
			ft_putstr("pb\n");
			if (stack->a_empty == FALSE && stack->a[stack->top_a] > stack->a[stack->top_a + 1])
			{
				if (stack->b_empty == FALSE && stack->top_b != stack->bottom - 1 && stack->b[stack->top_b] < stack->b[stack->top_b + 1])
				{
					solve_stack(stack, "ss");
					ft_putstr("ss\n");
				}
				else
				{
					solve_stack(stack, "sa");
					ft_putstr("sa\n");
				}
			}
			else if (stack->b_empty == FALSE && stack->top_b != stack->bottom - 1 && stack->b[stack->top_b] < stack->b[stack->top_b + 1])
			{
				solve_stack(stack, "sb");
				ft_putstr("sb\n");
			}
			//check if stack->b new top element is smaller than the stack->b bottom element
			// if (!(stack->b[stack->top_b < stack->b[stack->bottom - 1] && stack->a[top_a] > stack->b[stacl->top_b] && stack->a[top_a] < stack->b[stack->bottom - 1]))
			//	{
/*
					if (stack->b[stack->top_b < stack->b[stack->bottom - 1] && stack->a[top_a] < stack->a[stack->bottom - 1])
						solve_stack(stack, "rr");
						ft_putstr("rr\n");
					else if (stack->b[stack->top_b < stack->b[stack->bottom - 1])
						solve_stack(stack, "rb");
						ft_putstr("rb\n");
					else if (stack->a[top_a] < stack->a[stack->bottom - 1])
						solve_stack(stack, "ra");
						ft_putstr("ra\n");
*/
			//}
			
		}
		else if (stack->a_empty == FALSE && stack->a[stack->top_a] > stack->a[stack->top_a + 1])
		{
			if (stack->b_empty == FALSE && stack->top_b != stack->bottom - 1 && stack->b[stack->top_b] < stack->b[stack->top_b + 1])
			{
				solve_stack(stack, "ss");
				ft_putstr("ss\n");
			}
			else
			{
				solve_stack(stack, "sa");
				ft_putstr("sa\n");
			}
		}
		else if (stack->b_empty == FALSE && stack->top_b != stack->bottom - 1 && stack->b[stack->top_b] < stack->b[stack->top_b + 1])
		{
			solve_stack(stack, "sb");
			ft_putstr("sb\n");
		}
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




/*

	identify the lowest number location and try to get that to the bottom
	in the process of that move stuff in right order and move stuff to stack b
	weather the computer chooses to use rra or ra depends on which way is closest for it to get there in least amount of moves
	on the way the computer will check if any number is not in right order and will switch their position
	depending on which way we rotate the way we will switch will also change

	when lowest number is at the bottom 

	ex if putting top element in the bottom
		if (stack->a[top_a] < stack->a[top_a + 1])
			if (stack->a[stack->top_a + 1] > stack->a[stack->bottom - 1])
				switch(maybe also here with b_stack if possible)
		if (stack->a[top_a] > stack->a[stack->bottom - 1])
			reverse to bottom
		else
			push to b
				//make sure b is in order and if moves make sense to do on both stacks it will be done here
		to know weather to put current number to the bottom you check if the top number is bigger than the bottom number
		
	if puttting bottom to top
		if (nbr < nbr + 1)
			switch
		else
			keep position

	when stack a bottom is correct slowly move stuff to stack b until stack is down to two ordered stacks
	depending on which is longer we will do either rra or ra we rotate until the bottom ordered stack is on top and we will move stuff from stack b
	if the other sorted stack isn't the end we will move when stack->b top is smaller than the stack-a[bottom];


ALWAYS keep stack b in order as much as possible

	5
	3
	6
	4
	2
	0
	1

//rotate logic	
	ra
	pb
	ra
	pb
	pb
	rr
	ra
	pa
	pa
	pa
	rra
	rra





*/