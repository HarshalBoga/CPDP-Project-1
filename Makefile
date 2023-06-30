CFLAGS  = -std=gnu99 -Wall -pedantic -g
TARGETS = mytree mytree-o mytime mytime-o mymtimes mymtimes-o mytree.x mytime.x mymtimes.x

default: $(TARGETS)

mytree: mytree.c
	gcc $(CFLAGS) -c mytree.c
mytime: mytime.c
	gcc $(CFLAGS) -c mytime.c
mymtimes: mymtimes.c
	gcc $(CFLAGS) -c mymtimes.c
mytree-o: mytree.c
	gcc $(CFLAGS) -o mytree.o mytree.c
mytime-o: mytime.c
	gcc $(CFLAGS) -o mytime.o mytime.c
mymtimes-o: mymtimes.c
	gcc $(CFLAGS) -lm -o mymtimes.o mymtimes.c
mytree.x: mytree.c
	gcc $(CFLAGS) mytree.c -o mytree.x
mytime.x: mytime.c
	gcc $(CFLAGS) mytime.c -o mytime.x
mymtimes.x: mymtimes.c
	gcc $(CFLAGS) mymtimes.c -o mymtimes.x

clean:
	- rm -f *.o *.x *.cd Project_1