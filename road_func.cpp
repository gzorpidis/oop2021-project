#include <iostream>
#include <string.h>
#include "road.h"

using namespace std;


Car::Car(int i, int j): curr_segment(i), exit_segment(j), ready(0) {}


Entry::Entry(int k, int i): K(k), id(i) { 
    // toll construction
    // If we have one Toll**, we could say:
    // tolls (new Toll*[int number_of_tolls]) , where no_of_tolls is given
    int r1 = rand() % 5 + 1;
    toll_cash = new Toll_Cashier*[r1];
    int r2 = rand() % 4 + 1;
    toll_elec = new Toll_Electronic*[r2];

    for(int i = 0; i < r1; i++) {
        toll_cash[i] = new Toll_Cashier(K);
    }

    for(int i = 0; i < r2; i++) {
        toll_elec[i] = new Toll_Electronic(2*K);
    }
} 


Segment::Segment(int k, int cap, int i): 
capacity(cap), junction(i), 
// To start with, the segment is not connected with any other segment
prev_segment(NULL), next_segment(NULL)
{
  cout << junction << " segment Constructed\n";
  // K for the tolls, i-> position of the segment(and consequently the junction)
  entry = new Entry(k, i);

  // Create the starting cars
  for(int i = 0; i < capacity; i++) {

  }
  // print();
}

Segment::~Segment() {
  delete entry; // Deallocate the entry
}


Road::Road(int nsegs, int k, int per): NSegs(nsegs), K(k), Percent(per), 
segment( new Segment*[NSegs]) {
    cout << "Road Constructed\n";

    total_cars = 0;
    // segment = new Segment*[NSegs];

    for(int i = 0; i < NSegs; i++) {
        int cap;
        
        cap = rand() % 10; // To be changed to:
        // cout << "Give capacity for segment no: " << i + 1 << endl;
        // cin >> cap;

        // Create segment number i, with capacity cap, connected to the junction i
        // So the first segment [0] -> junction number: 0 , etc...
        segment[i] = new Segment(K, cap, i);
        
        // list<Car> list_of_cars;

        // construct cars to fill the segments
        // int cars = rand() % cap + 1;
        // for(int j = 0; j < cars; j++) {
        //     Car *car = new Car(i, rand() % NSegs);
        // rand() % (max_number + 1 - minimum_number) + minimum_number
        // Car(i, rand() % (NSegs + 1 -  ))
        //     segment[i]->enter(*car); 
        // }

        // total_cars += cars;
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

} 


////////////////////////////////////////////


void Road::operate() {

}


void Segment::enter(Car car) {
    // to enter ..
    
    // list_of_cars->push_back(car);
    curr_cars++;   // total?
}

void Segment::exit(Car car) {
    // to remove ..
    curr_cars--;   // total?
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
