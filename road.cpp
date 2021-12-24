#include <iostream>
#include <string.h>
#include "road.h"

using namespace std;



int main(int argc, char* argv[]) {
    int N = atoi(argv[1]);
    int NSegs = atoi(argv[2]);
    int K = atoi(argv[3]);
    int Percent = atoi(argv[4]);

    srand(time(nullptr));

    Road road(NSegs, K, Percent);
}