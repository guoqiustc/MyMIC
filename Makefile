mine: c_example.c mine.c mine.h
	cc -Wall -pg -o mine c_example.c mine.c -lm

clean:
	rm -rf *.o mine *.out result.txt
