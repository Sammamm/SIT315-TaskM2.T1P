#include <iostream>
// #include <cstdlib>
#include <chrono>
#include <fstream>
#include <ctime>
#include <pthread.h>

#define MAX_THREADS 4
#define MATRIX_SIZE 400

using namespace std::chrono;

int matrixA[MATRIX_SIZE][MATRIX_SIZE];
int matrixB[MATRIX_SIZE][MATRIX_SIZE];
int matrixC[MATRIX_SIZE][MATRIX_SIZE];
int thread_num = 0;
int partition_size = MATRIX_SIZE / MAX_THREADS;
void fillRandomMatrix(int matrix[][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            matrix[i][j] = rand() % 100;
        }
    }
}
void *multiplyMatrix(void *args)
{
    int thread = thread_num++;
    for (int i = thread * partition_size; i < (thread + 1) * partition_size; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            matrixC[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k)
            {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return NULL;
}
int main()
{
    srand(time(0));
    fillRandomMatrix(matrixA);
    fillRandomMatrix(matrixB);
    auto start = high_resolution_clock::now();
    pthread_t matrix_thread[MAX_THREADS];
    for (int i = 0; i < MAX_THREADS; ++i)
    {
        pthread_create(&matrix_thread[i], NULL, &multiplyMatrix, NULL);
    }
    for (int i = 0; i < MAX_THREADS; ++i)
    {
        pthread_join(matrix_thread[i], NULL);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    printf("Execution time: %d ms", duration.count());
    std::ofstream outputFile("pthread.txt");
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            outputFile << matrixC[i][j] << "\t";
        }
        outputFile << std::endl;
    }
    outputFile.close();
    return 0;
}
