PROG = lab03
OBJS = lab03.o sha256.o passwords.o

%.o: %.c
	gcc -c -g -o $@ $<

$(PROG): $(OBJS)
	gcc -g -o $@ $^

clean:
	rm -rf $(PROG) $(OBJS)
	rm Dictionary.txt
