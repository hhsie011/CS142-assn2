CC = g++
CFLAGS = -O2 -mcx16 -march=native -DCILK -fcilkplus -std=c++11

all:	reduce scan qsort parascan

reduce:	reduce.cpp
	$(CC) $(CFLAGS) -DNDEBUG reduce.cpp -o reduce
	
scan:	scan.cpp scan.h
	$(CC) $(CFLAGS) -DNDEBUG scan.cpp -o scan

qsort:	quicksort.cpp qsort.h
	$(CC) $(CFLAGS) -DNDEBUG quicksort.cpp -o qsort

parascan: parascan.cpp
	$(CC) $(CFLAGS) -DNDEBUG parascan.cpp -o parascan
	
clean:
	rm -f reduce scan qsort parascan
