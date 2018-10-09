objs = main.o wordcount.o

wordcount : $(objs)
	gcc -o wordcount $(objs) ./libdoull.a
main.o : main.c
	gcc -Wall -c main.c
wordcount.o : wordcount.c
	gcc -Wall -c wordcount.c

.PHONY : clean
clean:
	-rm $(objs)
