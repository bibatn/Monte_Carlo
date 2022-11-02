TARGET = monte_carlo

all: $(TARGET)

monte_carlo: header.h main.cpp 
	mpic++ -Wall -O3 main.cpp -lm -o monte_carlo

run: monte_carlo
	mpirun -np 1 ./monte_carlo 0.001

clean:
	rm -rf *.o $(TARGET)
	rm monte_carlo
