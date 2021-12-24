#include <iostream>
#include "odos.hpp"
#include <time.h>

using namespace std;

int main(int argc, char** argv) {
	// AttikiOdos att(3);
	// N, NSegs, K, Percent
	srand(time(NULL));
	if (argc == 2) {
		// int N = atoi(argv[1]);
		int NSegs = atoi(argv[1]);
		cout << "NSegs given: " << NSegs << endl;
		int K = atoi(argv[3]);
		int Percent = atoi(argv[4]);

		int** Seg_xor = new int*[NSegs];	// Create a array of the segments' capacity (could be int*, check it)

		// Οι χωρητικότητες των τμημάτων της Αττικής Οδού διαβάζονται από την καθιερωμένη είσοδο.
		for (int i = 0; i < NSegs; i++) {	
			int result;
			cout << "Give capacity for segment: " << i << endl;
			cin >> result;
			cout << "You gave: " << result << endl;
			Seg_xor[i] = new int(result);
		}

		AttikiOdos(NSegs, Seg_xor, K, Percent);

		// Delete these pointers
		for (int i = 0; i < NSegs; i++) {
			delete Seg_xor[i];
		}
		delete[] Seg_xor;
	}

	return 0;

}