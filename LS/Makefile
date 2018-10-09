objs = main.o ls.o

ls : $(objs)
	gcc -o Ls $(objs) ./libdoull.a
main.o : main.c
	gcc -Wall -c main.c
ls.o : ls.c
	gcc -Wall -c ls.c

.PHONY : clean
clean:
	-rm $(objs) Ls
