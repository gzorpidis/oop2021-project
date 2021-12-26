#include <iostream>
#include <string.h>
#include "road.h"
#include <stdlib.h>     /* srand, rand */
#include <cassert>

using namespace std;

Car::Car(int i, int j): curr_segment(i), exit_segment(j), ready(false) {}

// Get if a car is ready to leave its segment
bool Car::is_ready() const { return ready; }

// Get the index of the car's exit segment
int Car::get_exit_segment() const { return exit_segment; }

// Function to make a car's ready flag true, so it can leave the segment 
void Car::make_ready() { ready = true; }

// The segment which will create its entry will set the total number of tolls
Entry::Entry(int k, int i, int segments, int toll_number): K(k), id(i), no_of_tolls(toll_number) {
    

    // Make sure toll_numer is not 1, otherwise we will encounter an error because we want at least one of which (rand() will throw exception)
    assert(toll_number != 1);

    // Get the number of tolls with employees, and electronic
    // Rands are set in a way, such that at least one of them has at least one, so:
    // Employees in range: [1, toll_number - 1], so we can have at least 1 electronic and vise versa

    int w_employees = rand() % (toll_number - 1) + 1;
    int elec = toll_number - w_employees;

    assert(w_employees != 0);
    assert(elec != 0);


    cout << "Creating an entry with total: " << toll_number << " tolls, out\
    of which: " << w_employees << " have employees and: " << elec << " are \
    electronic!" << endl;

    // if we have K = 20
    // and we then have 4 tolls with employees we will have to have 20/4 = 5
    // in each toll, so if K are needed we can provide them
    // BUT if all enter, we will change K to K + 1 => 21 so now having 4
    // in each IS NOT SUFFICIENT!! we should be able to fix that!
    int cars_per_toll_cashiers;
    int cars_per_toll_elec;

    if (K % w_employees == 0)
      cars_per_toll_cashiers = K / w_employees;
    else
      cars_per_toll_cashiers = K / w_employees + 1;

    if (2 * K % elec == 0)
      cars_per_toll_elec = (2*K) / elec;
    else
      cars_per_toll_elec = (2*K) / elec + 1;
    
    cout << "cars_per_toll (cashiers) = " << K << " / " << w_employees << " = " << cars_per_toll_cashiers << endl;

    cout << "cars_per_toll (elec) = " << 2*K << " / " << elec << " = " << cars_per_toll_elec << endl;

    // create toll_number total tolls to begin with
    tolls = new Toll*[toll_number]; 
    

    // Will have to create cars that have current segment = -1
    // because they have not entered the highway yet, but they will
    // have to choose in which entry to leave, so they need
    // the segment in which they are created, as well as the total no of segments

    // Fill up the tolls
    for(int i = 0; i < w_employees; i++)
      tolls[i] = new Toll_Cashier(K, cars_per_toll_cashiers,id, segments);
    
    cout << endl;
    
    for(int i = w_employees; i < toll_number; i++)
      tolls[i] = new Toll_Electronic(2* K, cars_per_toll_elec,id, segments);

    cout << endl;

} 


Segment::Segment(int k, int cap, int i, int nsegs): 
capacity(cap), junction(i), no_of_segs(nsegs),
// To start with, the segment is not connected with any other segment
prev_segment(NULL), next_segment(NULL)
{
  cout << junction << " segment Constructed\n";

  // At least 2, because we need at least one of each!
  int no_of_tolls = rand() % 10 + 2;  

  // K-> the tolls, 
  // i-> position of the segment(and consequently the junction), 
  // the number of segments so the cars inside the entry can select the correct exit
  // and no_of_tolls for the entry
  entry = new Entry(k, i, no_of_segs, no_of_tolls);

  // Create the starting cars

  allocate_cars(capacity);  // Allocate capacity-space for the cars
  cout << "Now creating cars inside the road segment:" << endl;
  for(int j = 0; j < capacity; j++) {
    // rand() % (max_number + 1 - minimum_number) + minimum_number
    // exit specifies the node in which the car will exit (includes the last for now)
    int exit = rand() % (no_of_segs + 1 - (junction+1)) + (junction+1);
    cout << "Exit chosen:" << exit << endl;
    Car to_enter(j, exit);
    cars.push_back(to_enter); // push the car into the vector, calls copy constructor
  }
}

Segment::~Segment() {
  delete entry; // Deallocate the entry
}


Road::Road(int nsegs, int k, int per): NSegs(nsegs), K(k), Percent(per), 
segment( new Segment*[NSegs]) {
    cout << "Road Constructed\n";

    total_cars = 0;

    for(int i = 0; i < NSegs; i++) {
        int cap;
        
        cap = 4;
        // To be changed to:
        // cout << "Give capacity for segment no: " << i + 1 << endl;
        // cin >> cap;

        // Create segment number i, with capacity cap, connected to the junction i
        // So the first segment [0] -> junction number: 0 , etc...
        segment[i] = new Segment(K, cap, i, NSegs);
        
    }

    // After we have created the Segments, connect them
    for(int i = 0; i < NSegs; i++) {
      if (i == 0) {
        // First segment doesn't have a previous, so we only change the next
        segment[i]->connect_to_next(segment[i+1]);
      } else if ( i == NSegs - 1) {
        // Last segment doesn't have a next, so we only change the previous
        segment[i]->connect_to_previous(segment[i-1]);
      } else {
        // Else we change both next and previous
        segment[i]->connect_to_next(segment[i+1]);
        segment[i]->connect_to_previous(segment[i-1]);
      }
    }

    // Quick test for the segments
    segment[NSegs-1]->makeRandomReady();
    segment[NSegs - 1]->exit();

} 

// To delete the road, delete the Segments
Road::~Road() {
  for(int i = 0; i < NSegs; i++)
    delete segment[i];
  
  delete[] segment;
}


////////////////////////////////////////////


void Road::operate() {

}


void Segment::enter() {

    // for( auto it = cars.begin(); it != cars.end(); it++)
      
    // to enter ..
    
    // list_of_cars->push_back(car);
    // curr_cars++;   // total?
}

void Segment::exit() {
    // to remove ..

    // Gets the cars in the segment, iterate and find them
    // which want to exit at the next node
    cout << "Exiting cars from segment: " << junction << endl;
    for(auto it = cars.begin(); it != cars.end(); ) {
      if (it->is_ready() && it->get_exit_segment() == junction + 1 ) {
        int size_before_removal = cars.size();
        it = cars.erase(it);  // Removed car
        assert(size_before_removal == cars.size() + 1); // Assert changes where made
        
        cout << "Removed car successfully!" << endl;
      } else {
        ++it;
      }
    }
    // curr_cars--;   // total?
}

void Segment::pass() {
    
}

int Segment::get_no_of_vehicles() {
    return curr_cars;
}


void Segment::print() {
    cout << endl;
    for(int i = 0; i < capacity; i++) {
        cout << "-";
    }
    cout << endl;
    for(int i = 0; i < capacity; i++) {
        cout << "-";
    }
    cout << endl;
}

void Segment::connect_to_next(Segment* to_next) {
  next_segment = to_next;
}

void Segment::connect_to_previous(Segment* to_previous) {
  prev_segment = to_previous;
}

void Segment::iterate_segment_bw() {
  if (this->prev_segment == NULL) {
    cout << "Currently on segment: " << junction + 1 << "(first)" << endl;
    return;
  }
  cout << "Currently on segment: " << junction + 1 << endl;
  prev_segment->iterate_segment_bw();
}

void Segment::iterate_segment() {
  if (this->next_segment == NULL) {
    cout << "Currently on segment: " << junction + 1 << "(last)" << endl;
    return;
  }
  cout << "Currently on segment: " << junction + 1 << endl;
  next_segment->iterate_segment();
}

static double r2() {
	return (double)rand() / (double)RAND_MAX;
}


void Segment::makeRandomReady() {
  for(auto it = cars.begin(); it != cars.end(); it++) {
    if (r2() <= 0.5) {
      cout << "Random car made ready to leave!" << endl;
      it->make_ready();
    }
  }
}


Toll::Toll(int k, int in_each_toll, int id, int segments): K(k), max(in_each_toll), counter(0) {
    cout << "Toll(" << max << ")";
    cars.reserve(max);  // reserve that many spots to begin with

    for(int i = 0; i < max; i++) {
      int exit = rand() % (segments + 1 - (id+1)) + (id+1);
      cout << "Exit chose by car in toll:" << exit << endl;
      Car to_enter(-1, exit);
      cars.push_back(to_enter);   
      counter++;       
    }
    assert(counter == max);
}