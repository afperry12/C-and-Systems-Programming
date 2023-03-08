PROG = project02
OBJS = project02.o sha256.o

%.o: %.c
	gcc -c -g -o $@ $<

$(PROG): $(OBJS)
	gcc -g -o $@ $^

clean:
	rm -rf $(PROG) $(OBJS) dictionary.txt one-item-dictionary.txt spec-dictionary.txt two-item-dictionary.txt 1000-items-dictionary.txt
