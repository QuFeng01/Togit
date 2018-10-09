objs = demo.o gdllib.o
dllib : $(objs)
	gcc -o dllib $(objs)
demo.o : demo.c
	gcc -c demo.c
gdllib.o : gdllib.c gdllib.h
	gcc -c gdllib.c

.PHONY : clean
clean :
	rm $(objs) dllib
