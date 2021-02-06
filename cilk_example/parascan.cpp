#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "get_time.h"
using namespace std;

int th = 128;

void scan(int* A, int n, int& ps, int& leftSum) {
     if (n <= th) {
         for (int i = 0; i < n; i++) {
	     leftSum = A[i];
             A[i] = ps;
	     ps += leftSum;
         }
	 return;
     }
    cilk_spawn scan(A, n/2, ps, leftSum);
    scan(A+n/2, n-n/2, ps, leftSum);
    cilk_sync;
    return;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Usage: ./parascan [num_elements]" << endl;
		return 0;
	}
	int n = atoi(argv[1]);
	cout << n << endl;
	int* A = new int[n];
	int ps = 0;
	int leftSum = 0;
	cilk_for (int i = 0; i < n; i++) A[i] = i + 1;
	
	timer t; t.start();
	scan(A, n, ps, leftSum);
	t.stop(); cout << "time: " << t.get_total() << endl;
	
	//for (int i = 0; i < n; i++) cout << A[i] << " ";
	//cout << endl;

	cout << A[n-1] << endl;
  
    delete []A;
	
	return 0;
}
