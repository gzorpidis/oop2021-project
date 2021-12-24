#include <iostream>
#include <string.h>
#include "road.h"

using namespace std;


Car::Car(int i, int j): curr_segment(i), exit_segment(j), ready(0) {}


Entry::Entry(int k, int i): K(k), name(i) { 
    // toll construction
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


Segment::Segment(int k, int cap, int i): capacity(cap), junction(i) {
    cout << junction << "Segment Constructed\n";
    entry = new Entry(k, i);
    print();

}


Road::Road(int nsegs, int k, int per): NSegs(nsegs), K(k), Percent(per), segment( new Segment*[NSegs]) {
    cout << "Road Constructed\n";

    total_cars = 0;
    // segment = new Segment*[NSegs];

    for(int i = 0; i < NSegs; i++) {
        int cap;
        cap = rand() % 100 + 20; // cin >> c;

        segment[i] = new Segment(K, cap, i);
        
        // list<Car> list_of_cars;

        // construct cars to fill the segments
        int cars = rand() % cap + 1;
        for(int j = 0; j < cars; j++) {
            Car *car = new Car(i, rand() % NSegs);
            segment[i]->enter(*car); 
        }

        total_cars += cars;
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
