#include "odos.hpp"
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <stdlib.h>     /* srand, rand */

using namespace std;

AttikiOdos::AttikiOdos(int NSegs, int** segment_capacities, int k, int percent) :
no_of_cars(0),
segments( new Segment*[NSegs] ),
segment_no(NSegs)
{
	cout << "Αυτοκινητόδρομος σε λειτουργία" << endl;

	for(int i = 0; i < NSegs; i++) {
		if (i == 0) {
			// First Segment to be created must have a next segment, but the previous doesn't exist so NULL
			segments[i] = new Segment(*segment_capacities[i], &segments[i+1], NULL, 3, k, percent);
		} else if ( i < NSegs - 1) {
			segments[i] = new Segment(*segment_capacities[i], &segments[i+1], &segments[i-1], 3, k , percent);
		} else {
			// Last Segment to be created must have a previous segment, but the next doesn't exist so NULL
			segments[i] = new Segment(*segment_capacities[i], NULL,&segments[i-1], 3, k, percent);
		}
	}
}

AttikiOdos::~AttikiOdos() {
	for(int i = 0; i < segment_no; i++) {
		delete segments[i];
	}

	delete[] segments;
}

Segment::Segment(int max_capacity, Segment** next_seg, Segment** previous_seg, int toll_number, int k, int percent) : 
car_max(max_capacity), next(next_seg), prev(previous_seg), seg_entr(new Entrance(toll_number)) 
,K(k), Percent(percent)
{
	std::cout << "Created a Segment with max_cars: " << car_max << std::endl;
	if ( next == NULL) {
		cout << "This is the last segment, it has no next" << endl;
	} else if ( prev == NULL ) {
		cout << "This is the first segment, it has no previous" << endl;
	}

	int n = 4;	// Αρχικά, δημιουργούνται τυχαία αυτοκίνητα που κινούνται σε αυτό.
	// assert(n <= car_max);
	allocate_cars(n);	// If we do not do this, vector might call the copy constructor (if we want a cleaner outlook, have this) 

	cout << "Segment has " << n << " cars on it" << endl;
	for(int i = 0; i < n; i++) {
		cout << "Creating the:" << i + 1 << "th car" << endl;
		Car to_create(this);
		cars_on.push_back(to_create);
		cout << "Car vector size: " << cars_on.size() << endl;
		for(int i = 0; i < cars_on.size(); i++) {
			// assert(cars_on.at(i).current_segment == this);
			// assert(cars_on.at(i).curr_seg == -1);
		}
	}
	cout << "End of for loop!" << endl;
}

Segment::~Segment() {
	cout << "Destroying segment!" << endl;
	delete seg_entr;
}

static double r2() {
	return (double)rand() / (double)RAND_MAX;
}

Entrance::Entrance( int toll_number ) : tolls( new Tollbooth*[toll_number] )
{
	std:: cout << "Created an entrance!" << std::endl;
	for(int i = 0; i < toll_number; i++) {
		double result = r2();

		cout << "Result is: " << result << endl << endl;
		if (result <= 0.5) {
			tolls[i] = new E_Tb(this);
		} else {
			tolls[i] = new Employee_Tb(this);
		}
	}
};
