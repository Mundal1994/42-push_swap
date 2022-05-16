
#include "push_swap.h"
/*
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
}*/

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

static void	smallest_number(int *a, int small, int len)
{
	int	i;

	i = 0;
	small = a[0];
	while (i++ < len)
	{
		if (a[i] < small)
			small = a[i];
	}
}

static void	biggest_number(int *a, int big, int len)
{
	int	i;

	i = 0;
	big = a[0];
	while (i++ < len)
	{
		if (a[i] > big)
			big = a[i];
	}
}

static void	update_big_small(int *a, int small, int big)
{
	if (a[0] > big)
		big = a[0];
	else if (a[0] < small)
		small = a[0];
}

static void	push_and_update(t_stack *stack, char c)
{
	if (c == 'a')
	{
		if (stack->b_small == stack->b_big)//means one element left
		{
			stack->b_small = 1;
			stack->b_big = -1;
		}
		solve_stack(stack, "pa");
		ft_putstr("pa\n");
		update_big_small(&stack->a[stack->top_a], stack->a_small, stack->a_big);
		if (stack->a[stack->top_a] == stack->b_big)
			biggest_number(stack->b, stack->b_big, stack->bottom - stack->top_b);
		else if (stack->a[stack->top_a] == stack->b_small)
			smallest_number(stack->b, stack->b_small, stack->bottom - stack->top_b);
	}
	else
	{
		solve_stack(stack, "pb");
		ft_putstr("pb\n");
		if (stack->b_small > stack->b_big)//means stack is empty
		{
			stack->b_small = stack->b[stack->bottom - 1];
			stack->b_big = stack->b[stack->top_b];
		}
		update_big_small(&stack->b[stack->top_b], stack->b_small, stack->b_big);
		if (stack->b[stack->top_b] == stack->a_big)
			biggest_number(stack->a, stack->a_big, stack->bottom - stack->top_a);
		else if (stack->b[stack->top_b] == stack->a_small)
			smallest_number(stack->a, stack->a_small, stack->bottom - stack->top_a);
	}
	// maybe makes most sense here to check if stack b is sorted or not?? or maybe after moving stuff?
}

static void	switch_stacks(t_stack *stack, char c)
{
	if (c == 'a')
	{
		if (stack->b[stack->top_b] < stack->b[stack->top_b + 1])
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
	else
	{
		solve_stack(stack, "sb");
		ft_putstr("sb\n");
	}
}

static void	rotate_stacks(t_stack *stack, char c)
{
	if (c == 'r')
	{
		if (stack->b[stack->bottom - 1] > stack->b[stack->top_b])
		{
			solve_stack(stack, "rr");
			ft_putstr("rr\n");
		}
		else
		{
			solve_stack(stack, "ra");
			ft_putstr("ra\n");
		}
	}
	else
	{
		if (stack->b[stack->bottom - 1] > stack->b[stack->top_b])
		{
			solve_stack(stack, "rrr");
			ft_putstr("rrr\n");
		}
		else
		{
			solve_stack(stack, "rra");
			ft_putstr("rra\n");
		}
	}
}

static void	stage_one_sorting(t_stack *stack)
{
	/*
	ft_putstr("bigger than 3: ");
	ft_putnbr(stack->bottom - stack->top_a);
	ft_putchar('\n');
	*/
	if (stack->b_empty == FALSE && stack->b[stack->top_b] < stack->a[stack->top_a] && stack->b[stack->top_b] > stack->a[stack->bottom - 1])
	{
		push_and_update(stack, 'a');
	}
	else if (stack->a[stack->top_a + 3] < stack->a[stack->bottom - 1] && stack->a[stack->top_a + 2] > stack->a[stack->top_a + 3] && stack->bottom - stack->top_a > 5)
	{
		push_and_update(stack, 'b');
	}
	else if (stack->a[stack->bottom - 2] == stack->a_small && stack->a[stack->bottom - 1] == stack->a_big && stack->bottom - stack->top_a > 4)
	{
		// make function to check if this also needs to be done for stack->b
		rotate_stacks(stack, 'd');
		rotate_stacks(stack, 'd');
		switch_stacks(stack, 'a');
		rotate_stacks(stack, 'r');
	}
	else if (stack->a[stack->top_a] < stack->b_small && stack->bottom - stack->top_a > 4 && stack->b_empty == FALSE)
	{
		push_and_update(stack, 'b');
		// check if same can be done for stack a
		if (stack->bottom - stack->top_b < 4 && stack->a[stack->top_a] > stack->a[stack->top_a + 1])
		{
			switch_stacks(stack, 'a');
		}
		if (stack->b[stack->bottom - 1] > stack->b[stack->top_b])
		{
			solve_stack(stack, "rb");
			ft_putstr("rb\n");
		}
	}
	else if (stack->a[stack->top_a] > stack->a[stack->top_a + 1])
	{
		switch_stacks(stack, 'a');
	}
	else if (stack->a[stack->bottom - 1] > stack->a[stack->top_a] && stack->a[stack->bottom - 1] < stack->a[stack->top_a + 1])
	{
		if (stack->bottom - stack->top_a < 4)
		{
			rotate_stacks(stack, 'd');
			switch_stacks(stack, 'a');
		}
		else
		{
			push_and_update(stack, 'b');
			//if same can be done for stack b do rrr else
			rotate_stacks(stack, 'd');
		}
	}
	else if (stack->a[stack->bottom - 1] > stack->a[stack->top_a])
	{
		//if stack[bottom - 1] is heigher than any of them move it other side
		//if (stack->a[stack->bottom - 1] > stack->a[stack->top_a + 3])
		//{
			//if same can be done for stack b do rrr else
			//rotate_stacks(stack, 'd');
			/*
			if stack->b[top_a] != stack->b_heigh
				rrb or rb
			*/
			push_and_update(stack, 'b');
		/*}
		else if (stack->bottom - stack->top_a < 6)
		{
			push_and_update(stack, 'b');
		}
		else
		{*/
			//push_and_update(stack, 'b');
			//push_and_update(stack, 'b');
			//if same can be done for stack b do rrr else
			//rotate_stacks(stack, 'd');
		//}
	}
	else if (stack->a[stack->bottom - 1] < stack->a[stack->top_a])
	{
		//if same can be done for stack b do rrr else
		rotate_stacks(stack, 'd');
	}
	//solve_stack(stack, "sb");
	//ft_putstr("sb\n");
}

static void order_stack_b(t_stack *stack)
{
	// make it in order but if at any point it makes sense to push to stack a then do it
	if (stack->b[stack->top_b + 1] > stack->b[stack->top_b])
	{
		switch_stacks(stack, 'b');
	}
	// can make if statements to check if possible to push anythign to stack a
	//ex if I'm either at the top of b or bottom and that is bigger than bottom of a stack og smaller than top of a stack
	// that way i can keep shifting while trying to sort stack b
}

static void	stage_two_sorting(t_stack *stack)
{
	int	count;

	count = 1;
	while (is_stack_solved(stack->b, stack->top_b + 1, stack->bottom) == ERROR)
		order_stack_b(stack);
	if (stack->b_empty == FALSE)
	{
		if (stack->a[stack->bottom - 1] > stack->b[stack->top_b] && stack->a[stack->bottom - 2] < stack->b[stack->top_b])
		{
			rotate_stacks(stack, 'd');
			while (stack->a[stack->top_a] > stack->b[stack->top_b] && stack->a[stack->bottom - 1] < stack->b[stack->top_b])
			{
				push_and_update(stack, 'a');
				++count;
			}
			while (count-- > 0)
			{
				rotate_stacks(stack, 'r');
			}
		}
		else if (stack->b[stack->top_b] > stack->a[stack->top_a] && stack->b[stack->top_b] < stack->a[stack->top_a + 1])
		{
			rotate_stacks(stack, 'r');
			while (stack->a[stack->top_a] > stack->b[stack->top_b] && stack->a[stack->bottom - 1] < stack->b[stack->top_b])
				push_and_update(stack, 'a');
			rotate_stacks(stack, 'd');
		}
		else if (stack->b[stack->top_b] > stack->a[stack->bottom - 1])
		{
			push_and_update(stack, 'a');
			rotate_stacks(stack, 'r');
		}
		else if (stack->b[stack->top_b] < stack->a[stack->top_a])
		{
			//make a check for if stack b is at either b_big or b_bigB
			// if not loop to nearest
			push_and_update(stack, 'a');
		}
	}
	else
	{
		ft_putstr("error");
		exit(1);
	}

}

void	sort_stack(t_stack *stack)
{
	int	stage;

	//int i = 0;
	stage = 1;
	while (check_if_solved(stack, 'c') == ERROR)//i++ < 10 && 
	{
		if (stage == 1 && check_if_solved(stack, 'p') != ERROR)
			++stage;
		if (stage == 1)
		{
			stage_one_sorting(stack);
			//solve_stack(stack, "sb");
			//ft_putstr("stage1\n");
		}
		else if (stage == 2)
		{
			stage_two_sorting(stack);
			//ft_putstr("stage2\n");
		}
	}
	/*ft_putnbr(stack->a[0]);
	ft_putnbr(stack->a[1]);
	ft_putnbr(stack->a[2]);
	ft_putnbr(stack->a[3]);
	ft_putnbr(stack->a[4]);*/
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



two top and bottom compare method
./checker -5 8 -6 9 -9 10 2 3 1 4 0 -4 5 -8
rra
pb
pb
rra
rra
pb
rra
pb
rra
rra
pb
rra
rra
rra
pb
rra
pb
rb
rra
rra
sa
ra
pa
ra
ra
pa
pa
pa
pa
rra
pa
pa

32


jeffs method
./checker -5 8 -6 9 -9 10 2 3 1 4 0 -4 5 -8
pb
rra
pb
rrr
pb
rra
pb
sb
rra
pb
sb
rra
pb
sb
rra
rb
rb
pb
rrr
pb
sb
rra
rb
pb
sb
rrr
sa
rrr
pb
rra
sa
rb
pa
pa
pa
pa
pa
pa
pa
pa
rra
pa
pa

42





sort only top two and bottom
keep track of lowest and heighest number in each stack
stack->a_low
stack->a_heigh
stack->b_low
stack->b_heigh
stack->b_lowB
stack->b_heighB


pseudo code

stack->a_low = lowest_number
stack->a_heigh = heighest_number
stack->b_low = 1;
stack->b_heigh = -1;
stack->b_lowBig = 1;
stack->b_heighBig = -1;

stage = 1;
while (hasn't been solved)
{
	if (stack a get's solved and stack b is not empty)
		stage++;
	if (stage == 1)
	{
		if (stack->a[bottom - 2] == a_low && stack->a[bottom - 1] == stack->a_heigh)
			rra
			rra
			sa
			ra
		else if (stack->a[top_a] < stack->b_low)
			push to stack b
			rb
		else if (stack->a[top_a] > stack->a[top_a + 1])
		{
			if (same can be done for stack b)
				switch position ss
			else
				switch position sa
		}
		else if (stack->a[bottom - 1] > stack->a[top_a] && stack->a[bottom - 1] > stack->a[top_a + 1])
		{
			
			if (stack->a[bottom - 1] > stack->a[top_a + 3])
			{
				if (same can be done for stack b)
					rrr
				else
					rra
				push top elements to stack b
					if stack->b[top_a] != stack->b_heigh
						rrb or rb
				update
					stack->b_lowBig && b_heighBig
			}
			else
			{
				push two top elements to stack b
					if stack->b[top_a] != stack->b_heigh
						rrb or rb
				if (same can be done for stack b)
					rrr
				else
					rra
				update
					stack->b_low && b_heigh (only if heighter than what was previous heighest and lowest)
			}
		}
		else if (stack->a[bottom - 1] > stack->a[top_a] && tack->a[bottom - 1] < stack->a[top_a + 1])
		{
			push first element to stack b
				make sure in right order or else need to rotate before pushing
			if (same can be done for stack b)
				rrr
			else
				rra
			
		}
		else if (stack->a[bottom - 1] < stack->a[top_a])
		{
			if (same can be done for stack b)
				rrr
			else
				rra
		}
	}
	else if (stage == 2)
	{
		if (stack->b[top_b] == stack->b_heighBig)
		{
			pa
			update what is the new b_heighBig and b_lowBig
			update stack->a_low and a_heigh
			ra
		}
		else if (stack->b[top_b] == stack->b_heigh)
		{
			while (stack->a[top_a] < stack->b[top_b])
			{
				ra
			}
			while (stack->a[top_a] > stack->b[top_b] && stack->a[bottom - 1] < stack->b[top_b])
				pa
				update what is the new b_heighBig and b_lowBig
				update stack->a_low and a_heigh
			if (stack->a[bottom - 1] < stack->a[top_a])
				rra
		}

	}
}



*/