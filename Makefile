SRC_GS = generate_seq.c
SRC_CO = count_ps_ops.c count_ps_ops_utils.c
OBJ_GS = $(SRC_GS:.c=.o)
OBJ_CO = $(SRC_CO:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra

all: generate_seq count_ps_ops

generate_seq: $(OBJ_GS)
	$(CC) $(CFLAGS) $(OBJ_GS) -o $@ -lm

count_ps_ops: $(OBJ_CO) count_ps_ops.h
	$(CC) $(CFLAGS) $(OBJ_CO) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_GS) $(OBJ_CO)

fclean: clean
	rm -f generate_seq count_ps_ops

re: fclean all

.PHONY: all clean fclean re
