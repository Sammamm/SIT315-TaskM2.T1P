#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <omp.h>

#define MATRIX_SIZE 400

using namespace std::chrono;

int matrix1[MATRIX_SIZE][MATRIX_SIZE];
int matrix2[MATRIX_SIZE][MATRIX_SIZE];
int matrix3[MATRIX_SIZE][MATRIX_SIZE];

void randomMatrixValues(int matrix[][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            matrix[i][j] = rand() % 100;
        }
    }
}
int main()
{
    srand(time(0));
    randomMatrixValues(matrix1);
    randomMatrixValues(matrix2);
    auto start = high_resolution_clock::now();

#pragma omp parallel for
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            matrix3[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k)
            {
                matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    
    printf("Execution time: %d ms\n", duration.count());
    std::ofstream outputFile("openmp.txt");

    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            outputFile << matrix3[i][j] << "\t";
        }
        outputFile << std::endl;
    }
    outputFile.close();
    return 0;
}