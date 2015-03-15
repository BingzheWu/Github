test:homework2.o 
	g++ -o test homework1.o
homework2.o:homework1.cpp differential.h Matrix.h linear.h Vector.h
	g++ -c homework1.cpp
clean:
	rm -rf test
	rm -rf *.o

