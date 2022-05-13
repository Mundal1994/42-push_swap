
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
			if (stack->b_empty == FALSE && stack->a[stack->top_a] < stack->b[stack->top_b])
				//maybe check how to quickliest get it to the right position
				if (stack->a[top_a] > stack->b[top_b])
					if (stack->b[stack->top_b + 1] > stack->b[stack->bottom - 1])
						sb swap top of stack b
					//make some kind of looping either back and forward and have it loop back after pushing it to correct position
					//rr or rb thingy
					push to b
					// when moving it back we need to check if moving same direction would make sense for stack a
					//ex if stack->a[top_a] > stack->b[top_b + 1] && stack->a[top_a + 1] < stack->b[top_b + 1]
					// if this happens the next move HAS TO BE 'pa'
					// only can do this if bottom is lowest number and i have to make sure it is assembled in reverse order so i can push it to top of stack b

			if (stack->a[stack->top_a + 1] > stack->a[stack->bottom - 1])
				switch(maybe also here with b_stack if possible)
		if (stack->a[top_a] > stack->a[stack->bottom - 1])
			if (stack->b_empty == FALSE && stack->b[top_b] < stack->b[stack->bottom - 1])
				reverse to bottom rr
			else
				reverse to bottom ra
		else
			push to b
				//make sure b is in order and if moves make sense to do on both stacks it will be done here
		to know weather to put current number to the bottom you check if the top number is bigger than the bottom number
		
		when biggest number is at bottom
		if (stack->a[top_a] < stack->a[top_a + 1])

	if putting bottom to top
		if (nbr < nbr + 1)
			switch
		else
			keep position

	when stack a bottom is correct slowly move stuff to stack b until stack is down to two ordered stacks
	depending on which is longer we will do either rra or ra we rotate until the bottom ordered stack is on top and we will move stuff from stack b
	if the other sorted stack isn't the end we will move when stack->b top is smaller than the stack-a[bottom];


when two sorted stacks in stack a and one sorted stack b i will merge them together

check at what point in the array of stack->a is sorted correctly

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






./checker 0 4 7 -9 9 2 10 -4 5 3 1 8 -6 6
pb
pb
ra
pb
rr
pb
sb
ra
rrb
pb
rb
rr
pb
sb
rra
pb
rrb
rrb
rrb
pb
sa
rb
rb
rb
pb
rb
rr
pb
pb
rra
pa
pa
pa
pa
pa
pa
pa
pa
pa
pa
pa

41




moving it downwards instead of up rra
pb
pb
rra
rra
pb
rb
pb
pb
pb
rr
sa
rr
rb
rb
pb
rb
rb
pb
sa
rrb
rrb
pb
sa
pb
rrb
pb
rrb
rrb
pa
pa
pa
pa
sb
pa
sb
pa
pa
pa
pa
pa
pa


41


top two and bottom system
pb
rra
sa
rra
pb
pb
rrb
sb
pb
sa
pb
rra
sa
rra
rb
pa
rra
pb
rra
rra
ss
pb
sb
pa
pa
rra
pb
rra
rra
ss
ra
pa
sb
pa
pa
pa
pa

37

keep track of top and bottom in each stack so i then can know if they have been divided with all the numbers


./checker 5 4 3 2 1
ra
sa
pb
sa
pb
ss
ra
pa
pa
rra

10

keep middle 3 everything else goes to stack b

pb
pb
ra
ss
pa
pa
ra
ra

8

jefs version

sa
ra
pb
ra
pb
ra
pa
pa

8

./checker 9 8 7 6 5 4 3
sa
rra
pb
rra
pb
rra
pb
rra
pb
rra
pa
pa
pa
pa

14

ra
sa
pb
sa
pb
ss
pb
sa
rb
pb
rb
sa
pb
rb
pa
pa
pa
pa
pa

19



sort only top two and bottom
sa
rra
rra
sa
pb
rra
sa
pb
rra
sa
pb
rra
sa
pa
pa
pa

16


./checker 8 4 9 3 6 5 7
sa
rra
sa
rra
sa
pa
rra
sa
rra
pa
sa

11




keep track of lowest and heighest number in each stack
stack->b_low
stack->b_heigh


*/