#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>
#include <chrono>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {
	int i = 0;
	int n = 2048;
	int countProcs, rank, size;
	double time, start, end;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &countProcs);
	int line = n * n / countProcs;
	int* firstMatrix = nullptr, * transponseSecondMatrix = nullptr, * result = nullptr;

	if (rank == 0) {
		FILE* Read = NULL;
		fopen_s(&Read, "matrix1.bin", "rb");
		firstMatrix = new int[n * n];
		fread(firstMatrix, sizeof(int), n * n, Read);
		fclose(Read);
		fopen_s(&Read, "matrix2.bin", "rb");
		int* secondMatrix = new int[n * n];
		fread(secondMatrix, sizeof(int), n * n, Read);
		fclose(Read);
		transponseSecondMatrix = new int[n * n];
		start = MPI_Wtime();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				transponseSecondMatrix[i * n + j] = secondMatrix[j * n + i];
			}
		}
		delete[] secondMatrix;
		secondMatrix = nullptr;
		result = new int[n * n];
		size = n;
	}
	MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if (rank) {
		transponseSecondMatrix = new int[size * size];
	}
	int localSize = size / countProcs;
	int* locPart = new int[localSize * size];
	int* locRes = new int[localSize * size];
	MPI_Scatter(firstMatrix + rank * size * localSize, size * localSize, MPI_INT, locPart, size * localSize, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(transponseSecondMatrix, size * size, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < localSize; ++i) {
		for (int j = 0; j < size; ++j) {
			locRes[i * size + j] = 0;
			for (int k = 0; k < size; ++k) {
				locRes[i * size + j] += locPart[i * size + k] * transponseSecondMatrix[j * size + k];
			}
		}
	}
	MPI_Gather(locRes, localSize * size, MPI_INT, result, size * localSize, MPI_INT, 0, MPI_COMM_WORLD);
	end = MPI_Wtime();
	if (rank) {
		delete[] transponseSecondMatrix;
		delete[] locRes;
		delete[] locPart;
	}
	MPI_Finalize();
	delete[] firstMatrix;
	delete[] transponseSecondMatrix;
	FILE* Write = nullptr;
	fopen_s(&Write, "result.bin", "wb");
	fwrite(result, sizeof(int), size * size, Write);
	fclose(Write);
	delete[] result;
	std::cout << "Time: " << (end - start) * 1000 << std::endl;
	return 0;
}


