#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

const int MATRIX_SIZE = 400;

void fillMatrixWithRandomValues(int matrix[][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            matrix[i][j] = rand() % 100;
        }
    }
}

void multiplyMatrices(const int matrix1[][MATRIX_SIZE], const int matrix2[][MATRIX_SIZE], int resultMatrix[][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k)
            {
                resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

int main()
{
    srand(time(nullptr));

    int matrix1[MATRIX_SIZE][MATRIX_SIZE];
    int matrix2[MATRIX_SIZE][MATRIX_SIZE];
    int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];

    fillMatrixWithRandomValues(matrix1);
    fillMatrixWithRandomValues(matrix2);

    auto startTime = std::chrono::high_resolution_clock::now();
    multiplyMatrices(matrix1, matrix2, resultMatrix);
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);

    std::cout << "Execution Time: " << duration.count() << " ms" << std::endl;

    std::ofstream outputFile("sequential.txt");
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            outputFile << resultMatrix[i][j] << "\t";
        }
        outputFile << std::endl;
    }
    outputFile.close();

    return 0;
}
