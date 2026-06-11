#include "count_ps_ops.h"

void free_stacks(t_ps* ps) {
	if (ps->a.val)
		free(ps->a.val);
	if (ps->b.val)
		free(ps->b.val);
}

void exit_gracefully(t_ps* ps) {
	free_stacks(ps);
	fprintf(ps->fptr, "Error\n");
	exit(1);
}

void ps_init(t_ps* ps, int size) {
	stack_init(&ps->a, size);
	if (!ps->a.val)
		exit_gracefully(ps);
	stack_init(&ps->b, size);
	if (!ps->b.val)
		exit_gracefully(ps);
}

void stack_init(t_stack* a, int size) {
	a->size = 0;
	a->val = malloc(size * sizeof(int));
}

void stack_add_back(t_stack* a, int val) {
	a->val[a->size] = val;
	a->size++;
}

bool is_sorted(t_stack* a) {
	int i;

	i = 1;
	while (i < a->size) {
		if (a->val[i - 1] > a->val[i])
			return (false);
		i++;
	}
	return (true);
}

void stack_rank(t_stack* dest, t_stack* src) {
	int i;
	int j;
	int rank;

	i = 0;
	while (i < src->size) {
		rank = 0;
		j = 0;
		while (j < src->size) {
			if (src->val[j] < src->val[i])
				rank++;
			j++;
		}
		dest->val[i] = rank;
		i++;
	}
	dest->size = src->size;
	src->size = 0;
}

void push(t_stack* a, t_stack* b) {
	if (b->size == 0)
		return;
	stack_add_back(a, b->val[0]);
	reverse_rotate(a);
	rotate(b);
	b->size--;
}

void pa(t_ps* ps) {
	push(&ps->a, &ps->b);
	ps->count_ops++;
}

void pb(t_ps* ps) {
	push(&ps->b, &ps->a);
	ps->count_ops++;
}

void swap(t_stack* a) {
	int tmp;

	if (a->size <= 1)
		return;
	tmp = a->val[0];
	a->val[0] = a->val[1];
	a->val[1] = tmp;
}

void sa(t_ps* ps) {
	swap(&ps->a);
	ps->count_ops++;
}

void sb(t_ps* ps) {
	swap(&ps->b);
	ps->count_ops++;
}

void ss(t_ps* ps) {
	swap(&ps->a);
	swap(&ps->b);
	ps->count_ops++;
	ps->count_ops++;
}

void rotate(t_stack* a) {
	int i;
	int tmp;

	tmp = a->val[0];
	i = 1;
	while (i < a->size) {
		a->val[i - 1] = a->val[i];
		i++;
	}
	a->val[i - 1] = tmp;
}

void ra(t_ps* ps) {
	rotate(&ps->a);
	ps->count_ops++;
}

void rb(t_ps* ps) {
	rotate(&ps->b);
	ps->count_ops++;
}

void rr(t_ps* ps) {
	rotate(&ps->a);
	rotate(&ps->b);
	ps->count_ops++;
}

void reverse_rotate(t_stack* a) {
	int i;
	int tmp;

	i = a->size - 1;
	tmp = a->val[i];
	while (i > 0) {
		a->val[i] = a->val[i - 1];
		i--;
	}
	a->val[0] = tmp;
}

void rra(t_ps* ps) {
	reverse_rotate(&ps->a);
	ps->count_ops++;
}

void rrb(t_ps* ps) {
	reverse_rotate(&ps->b);
	ps->count_ops++;
}

void rrr(t_ps* ps) {
	reverse_rotate(&ps->a);
	reverse_rotate(&ps->b);
	ps->count_ops++;
}
