#include <iostream>
#include <omp.h>
#include <string>
using namespace std;


//Parallel multiplication with OpenMP
float** omp_multiplication(float** A, float** B, float** C, int N) {
#pragma omp parallel for shared(A, B, C)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < N; k++) C[i][j] += A[i][k] * B[k][j];
        }
    }
    return C;
}

//Returns true if positive number
bool input_check(const string s) {
    if (s.find_first_not_of("0123456789") == std::string::npos)
        return stoi(s) >= 0;
    else
        return false;
}

//Makes multiplication with all existing threads. Shows time for every thread.
void mul_with_existing_threads(float** A, float** B, float** C, int N) {
    float t1, t2;
    for (int i = 1; i <= omp_get_num_procs(); i++) {
        omp_set_num_threads(i);
        t1 = omp_get_wtime();
        C = omp_multiplication(A, B, C, N);
        t2 = omp_get_wtime();
        cout << "Theads number: " << i << endl;
        cout << "Multiplication time: " << t2 - t1 << endl;
    }
}

int main() {
    string input;
    int i, j, k, N;

    cout << "Input N: ";
    getline(cin, input);
    if (input_check(input))
        N = stoi(input);
    else {
        cout << "Incorect input" << endl;
        return 1;
    }

    float** a = new float* [N];
    for (i = 0; i < N; i++)
        a[i] = new float[N];

    float** b = new float* [N];
    for (i = 0; i < N; i++)
        b[i] = new float[N];

    float** c = new float* [N];
    for (i = 0; i < N; i++)
        c[i] = new float[N];

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            a[i][j] = b[i][j] = i * j;


    mul_with_existing_threads(a, b, c, N);

    return 0;
}