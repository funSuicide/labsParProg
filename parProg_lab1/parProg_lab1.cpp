#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>
#include <chrono>

using namespace std;

void printMatrix(vector<vector<int>>  src) {
	for (auto it = src.begin(); it != src.end(); ++it) {
		for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
}

void readMatrix(vector<vector<int>>& src, const char* path, int max_x, int max_y) {
	ifstream fin(path);
	int tmp;
	for (int i = 0; i < max_y; i++) {
		vector<int> temp;
		src.push_back(temp);
		for (int j = 0; j < max_x; j++) {
			fin >> tmp;
			src[i].push_back(tmp);
		}
	}
}

vector<vector<int>> multiplicationMatrix(vector<vector<int>>& src1, vector<vector<int>>& src2) {
	int row1 = src1.size();
	int col1 = src1[0].size();
	int col2 = src2[0].size();
	vector<vector<int>> result;
	result.reserve(row1);
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < row1; i++) {
		vector<int> tmp(col2);
		result.push_back(tmp);
		result[i].reserve(col2);
		for (int j = 0; j < col2; j++) {
			result[i][j] = 0;
			for (int k = 0; k < col1; k++) {
				result[i][j] += src1[i][k] * src2[k][j];
			}
		}
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;
	cout << "sizeMatrix: " << src1.size() << "x" << src1[0].size() << std::endl;
	cout << "timeMultiplication: " << elapsed.count() << endl;
	ofstream out("results.txt", ios::app);
	out << elapsed.count() << " ";
	return result;
}

void writeMatrix(vector<vector<int>>& src, const char* path, int max_x, int max_y) {
	ofstream out(path);
	int tmp;
	for (int i = 0; i < max_y; i++) {
		for (int j = 0; j < max_x; j++) {
			tmp = src[i][j];
			out << tmp << " ";
		}
		out << endl;
	}
}

int main() {
	int i = 0;
	int n = 2048;
	vector<vector<int>> A;
	vector<vector<int>> B;
	readMatrix(A, "matrix1.txt", n, n);
	readMatrix(B, "matrix2.txt", n, n);
	while (i < 5) {
		vector<vector<int>> C(multiplicationMatrix(A, B));
		writeMatrix(C, "result.txt", n, n);
		i++;
	}
}
