OBJ1=idea.o
OBJ2=ideatest.o

all:libtest.a idea

clean:
	@- rm -f *.o libtest.a idea

libtest.a: $(OBJ1)
	ar -cur $@ $?
	@chmod  666 $@

idea:$(OBJ2)
	cc -o idea ideatest.o -L./ -ltest
.c.o:
	cc  -c $<

