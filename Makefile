TARGET = monte_carlo

all: $(TARGET)

monte_carlo: header.h main.cpp 
	mpic++ -Wall -O3 main.cpp -lm -o monte_carlo

clean:
	rm -rf *.o $(TARGET)
	rm monte_carlo
