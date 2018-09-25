CFLAGS=--std=c++11

p1.x:
	gcc p1.c -o p1.x

p2.x:
	gcc p2.c -o p2.x

p3.x:
	g++ $(CFLAGS) p3.cpp -o p3.x

p3.s: 
	g++ $(CFLAGS) -S p3.cpp -o p3.s

p4.x:
	g++ $(CFLAGS) p4.cpp -o p4.x

p4_pb.x:
	g++ $(CFLAGS) p4_pb.cpp -o p4_pb.x

dumpVDSOTable: p4_pb.x
	./p4_pb.x vdso.data vdso
	objdump -T vdso.data

clean:
	rm *.x *.s

all: p1.x p2.x p3.x p3.s p4.x p4_pb.x dumpVDSOTable