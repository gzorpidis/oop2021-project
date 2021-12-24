#include <iostream>
#include <string.h>
#include <list>
#include <vector>

using namespace std;

class Segment;
class Toll;


class Toll {
    private:
        int K;
    public:
        Toll(int k): K(k) {
            cout << "Toll ";
        }
};

class Toll_Electronic : public Toll {
    private:
    public:
        Toll_Electronic(int k): Toll(k) {
            cout << "Elec | ";
        }
};

class Toll_Cashier : public Toll {
    private:
    public:
        Toll_Cashier(int k): Toll(k) {
            cout << "Cash | ";
        }
};


class Car {
    private:
        bool ready; 
        int curr_segment;
        int exit_segment;
    public:
        Car(int ,int);
};


class Entry {
    private:
        // Could also be one array, i.e. Toll** tolls;
        Toll_Electronic **toll_elec;
        Toll_Cashier **toll_cash;
        int id;
        int K;
    public:
        Entry(int, int);
        void operate();
};


class Segment {
    private:
        int junction;
        int curr_cars; // 
        int capacity;
        Entry *entry;
        Segment *prev_segment;
        Segment *next_segment;
        vector<Car> cars;
        // list<Car> list_of_cars;

    public:
        Segment(int, int, int);
        ~Segment();
        // Functions to connect the pointers of the segments, after they have all been created!
        void connect_to_previous(Segment* to_prev);
        void connect_to_next(Segment* to_next);


        void enter(Car);
        void exit(Car);
        void pass();
        int get_no_of_vehicles();
        void operate();

        void print();

        // Test functions to iterate a segment using the pointers
        void iterate_segment();
        void iterate_segment_bw();
};


class Road {
    private:
        int N, NSegs, K, Percent; 
        Segment **segment;
        int total_cars; 
    public:
        Road(int, int, int); 
        void operate();
};