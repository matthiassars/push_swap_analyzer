#ifndef COUNT_PS_OPS_H
#define COUNT_PS_OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

typedef struct s_stack {
	int* val;
	int size;
} t_stack;

typedef struct s_ps {
	t_stack a;
	t_stack b;
	int count_ops;
	FILE* fptr;
} t_ps;

void stack_init(t_stack* a, int size);
void stack_add_back(t_stack* a, int val);
bool is_sorted(t_stack* a);
void stack_rank(t_stack* dest, t_stack* src);
void swap(t_stack* a);
void push(t_stack* a, t_stack* b);
void rotate(t_stack* a);
void reverse_rotate(t_stack* a);
void sa(t_ps* ps);
void sb(t_ps* ps);
void ss(t_ps* ps);
void pa(t_ps* ps);
void pb(t_ps* ps);
void ra(t_ps* ps);
void rb(t_ps* ps);
void rr(t_ps* ps);
void rra(t_ps* ps);
void rrb(t_ps* ps);
void rrr(t_ps* ps);
void ps_init(t_ps* ps, int size);
void free_stacks(t_ps* ps);
void exit_gracefully(t_ps* ps);

#endif
