all: seq_multiply par_multiply_outer par_multiply_second par_multiply_inner seq_strassen par_strassen

seq_multiply: seq_multiply.c
	gcc $? -o $@

par_multiply_outer: par_multiply_outer.c
	gcc $? -o $@ -lpthread -lm

par_multiply_second: par_multiply_second.c
	gcc $? -o $@ -lpthread -lm

par_multiply_inner: par_multiply_inner.c
	gcc $? -o $@ -lpthread -lm

seq_strassen: seq_strassen.c
	gcc $? -o $@

par_strassen: par_strassen.c
	gcc $? -o $@ -lpthread -lm

.PHONY: clean
clean:
	rm -f seq_multiply par_multiply_outer par_multiply_second par_multiply_inner seq_strassen par_strassen

