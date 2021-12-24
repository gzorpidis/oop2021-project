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
            cout << "Tool ";
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
        Toll_Electronic **toll_elec;
        Toll_Cashier **toll_cash;
        int name;
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
        Segment *prev_segment; //
        Segment *next_segment; //
        vector<Car> cars;
        // list<Car> list_of_cars;

    public:
        Segment(int, int, int);
        void enter(Car);
        void exit(Car);
        void pass();
        int get_no_of_vehicles();
        void operate();

        void print();
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