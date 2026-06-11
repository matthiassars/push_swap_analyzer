#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

void swap(int* a, int* b) {
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

float compute_disorder(int* a, int size) {
	if (size <= 1)
		return (0);
	int	mistakes = 0;
	int	total_pairs = 0;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			total_pairs++;
			if (a[i] > a[j])
				mistakes++;
		}
	}
	return ((float)mistakes / total_pairs);
}

int	main(int argc, char** argv) {
	srand(time(NULL) ^ getpid());

	char filename[256];
	*filename = '\0';
	int size = rand() % 1024 + 1;
	float disorder = (float)rand() / (float)RAND_MAX;

	for (int i = 1; i < argc; i += 2) {
		if (strcmp(argv[i], "-o") == 0)
			strcpy(filename, argv[i + 1]);
		else if (strcmp(argv[i], "-n") == 0)
			size = atoi(argv[i + 1]);
		else if (strcmp(argv[i], "-m") == 0)
			size = rand() % atoi(argv[i + 1]) + 1;
		else if (strcmp(argv[i], "-d") == 0)
			disorder = atof(argv[i + 1]);
		else {
			printf("Error");
			return (1);
		}
	}

	bool descending = false;
	if (disorder > .5f) {
		descending = true;
		disorder = 1.f - disorder;
	}
	if (disorder > .499999f)
		disorder = .499999f;
	int n_swaps = 0;
	if (size > 2)
		n_swaps = roundf(logf(1.f - disorder * 2.f) / logf(1.f - 2.f / size));

	int* a = malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
		a[i] = (descending) ? size - 1 - i : i;
	for (int i = 0; i < n_swaps; i++)
		swap(a + rand() % size, a + rand() % size);
	for (int i = 0; i < size; i++)
		printf("%d ", a[i]);
	printf("\n");

	FILE* fptr = stderr;
	if (*filename) {
		fptr = fopen(filename, "a");
		if (!fptr) {
			printf("Error opening file\n");
			return (1);
		}
	}

	fprintf(fptr, "%d,%f,", size, compute_disorder(a, size));
	if (fptr == stderr)
		fprintf(fptr, "\n");

	if (fptr != stderr)
		fclose(fptr);
}
