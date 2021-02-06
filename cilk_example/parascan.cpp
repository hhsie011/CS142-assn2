#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "get_time.h"
using namespace std;

int th = 128;

void scan(int* A, int n, int& ps, int& leftSum) {
    // if (n <= th) {
    //     int ret = 0;
    //     for (int i = 0; i < n; i++) {
    //         ret += A[i];
    //     }
    //     return ret;
	// }
    if (n == 1) {
        leftSum += A[0];
        A[0] = ps;
    }
    cilk_spawn scan(A, n/2, ps);
    scan(A+n/2, n-n/2, ps);
    cilk_sync;
    return;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Usage: ./scan [num_elements]" << endl;
		return 0;
	}
	int n = atoi(argv[1]);
	cout << n << endl;
	int* A = new int[n];
	
	timer t; t.start();
	scan(A, n, 0, 0);
	t.stop(); cout << "time: " << t.get_total() << endl;
	
	for (int i = 0; i < n; i++) cout << A[i] << " ";
	cout << endl;
  
    delete []A;
	
	return 0;
}