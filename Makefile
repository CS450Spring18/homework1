runP1:
	gcc p1.c -o p1.o
	echo "make sure to kill these processes"
	./p1.o & ./p1.o &

runP2:
	gcc p2.c -o p2.o
	./p2.o

runP3:
	g++ p3.cpp -o p3.o
	./p3.o

runP4:
	g++ p4.cpp -o p4.o
	./p4.o

runP4PB:
	g++ p4_pb.cpp -o p4_pb.o
	./p4_pb.o vdso.data vdso

dumpVDSOTable: runP4PB
	objdump -T vdso.data

clean:
	rm *.o*
