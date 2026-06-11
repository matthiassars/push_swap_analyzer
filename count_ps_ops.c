#include "count_ps_ops.h"

void ps_op(t_ps* ps, char* str) {
	if (strcmp(str, "sa\n") == 0)
		sa(ps);
	else if (strcmp(str, "sb\n") == 0)
		sb(ps);
	else if (strcmp(str, "ss\n") == 0)
		ss(ps);
	else if (strcmp(str, "pa\n") == 0)
		pa(ps);
	else if (strcmp(str, "pb\n") == 0)
		pb(ps);
	else if (strcmp(str, "ra\n") == 0)
		ra(ps);
	else if (strcmp(str, "rb\n") == 0)
		rb(ps);
	else if (strcmp(str, "rr\n") == 0)
		rr(ps);
	else if (strcmp(str, "rra\n") == 0)
		rra(ps);
	else if (strcmp(str, "rrb\n") == 0)
		rrb(ps);
	else if (strcmp(str, "rrr\n") == 0)
		rrr(ps);
	else
		exit_gracefully(ps);
}

int main(int argc, char** argv) {
	char filename[256];
	*filename = '\0';
	t_ps ps;
	bzero(&ps, sizeof(ps));

	if (argc <= 1)
		return(1);
	int i = 1;
	for (; i < argc + 1 && argv[i][0] == '-'; i += 2) {
		if (strcmp(argv[i], "-o") == 0)
			strcpy(filename, argv[i + 1]);
		else
			exit_gracefully(&ps);
	}
	if (argc - i <= 0)
		return(1);
	ps_init(&ps, argc - i);
	for (; i < argc; i++)
		stack_add_back(&ps.b, atoi(argv[i]));

	if (!*filename)
		ps.fptr = stdout;
	else {
		ps.fptr = fopen(filename, "a");
		if (!ps.fptr)
			exit_gracefully(&ps);
	}

	stack_rank(&ps.a, &ps.b);
	char str[5];
	while (fgets(str, 5, stdin) != NULL)
		ps_op(&ps, str);

	bool ok = (is_sorted(&ps.a) && ps.b.size == 0);
	if (ok)
		fprintf(ps.fptr, "%d,", ps.count_ops);
	else
		fprintf(ps.fptr, "KO,");
	if (ps.fptr == stdout)
		fprintf(ps.fptr, "\n");

	if (ps.fptr != stdout)
		fclose(ps.fptr);
	free_stacks(&ps);

	return (ok ? 0 : 1);
}
