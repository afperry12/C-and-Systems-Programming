PROG = lab04 test
OBJS = lab04.o test.o

%.o: %.c
	gcc -c -g -o $@ $< -lm

$(PROG): $(OBJS)
	gcc -g -o $@ $^ -lm

clean:
	rm -rf $(PROG) $(OBJS)
