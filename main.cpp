#include "header.h"

using namespace std;

int main(int argc, char **argv) {
	int rank = -1;
	int iter_count = 1;
	int is_tol_enough = 0;
	double start_time = 0;
	double prog_time = 0;
	double count_value = 0;
	double tol = 0;
	double current_sum = 0;
	double res_value = 0;
	double all_sum = 0;
	double epsilon = 0.001;
	double max_prog_time = 0;

	MPI_Init(&argc, &argv);
    if(argc < 2)
    {
        print_usage();
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    epsilon = atof(argv[1]);
	MPI_Comm_size(MPI_COMM_WORLD, &NODE_COUNT);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	srand(rank + 1);
	
	// Start
	start_time = MPI_Wtime();

	while (!is_tol_enough && iter_count < MAX_ITER_COUNT)
    {
		// Generate sum of F func values
		current_sum = generate_values();

		MPI_Reduce(&current_sum, &all_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		if (rank == 0)
        {
			count_value += all_sum;
			res_value = VOLUME * count_value / iter_count;
			tol = abs(I - res_value);

			if (tol < epsilon)
            {
				is_tol_enough = true;
			}
		}
            MPI_Bcast(&is_tol_enough, 1, MPI_INT, 0, MPI_COMM_WORLD);


        iter_count++;
	}
	
	prog_time = MPI_Wtime() - start_time;

	if (!is_tol_enough)
    {
        std::cout << "Пройдено максимальное кол-во итераций." << std::endl;
	}
	else
    {
        std::cout << "Решение сошлось к заданной наперед точности." << std::endl;
	}
//    std::cout << "I'm here1" << std::endl;


	// Display result
	if (rank == 0)
    {
        std::cout << "Proc count: " << NODE_COUNT << "\nepsilon: " << epsilon << std::endl;
        std::cout << "Result: " << res_value << "\nTol: " << tol << "\nTime: " << prog_time << std::endl;
	}
//    std::cout << "I'm here2" << std::endl;

	MPI_Finalize();
	return 0;
}

double f_func(double x, double y, double z)
{
	double res = 0;
	if (z >= sqrt(x*x + y*y)) {
		res = sqrt(x*x + y*y);
	}
	return res;
}

double generate_values()
{
	double current_sum = 0;
	double x, y, z;
	for (uint64_t i = 0; i < MAX_SAMPLES_COUNT; i++)
    {
		x = (double)rand() / RAND_MAX;
		y = (double)rand() / RAND_MAX;
		z = (double)rand() / RAND_MAX;
		current_sum += f_func(x, y, z);
	}
	return current_sum / (NODE_COUNT * MAX_SAMPLES_COUNT);
}

void print_usage()
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank==0)
    {
        printf("Usage: mpirun -np [num-procs] ./monte_carlo [epsilon-value]\n");
    }
}
