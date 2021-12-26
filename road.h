#include <iostream>
#include <string.h>
#include <list>
#include <vector>

using namespace std;

class Segment;
class Toll;
class Car;

class Toll {
    private:
        int K;
        vector<Car> cars;
        int max;
        int counter;

    public:
        Toll(int k, int in_each_toll, int id, int segments);
};

class Toll_Electronic : public Toll {
    private:
    public:
        Toll_Electronic(int k, int in_each_toll, int id, int segments): Toll(k, in_each_toll, id, segments) {
            cout << "Elec | ";
        }
};

class Toll_Cashier : public Toll {
    private:
    public:
        Toll_Cashier(int k, int in_each_toll, int id, int segments): Toll(k, in_each_toll,id, segments) {
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
        Car(const Car& temp) : curr_segment(temp.curr_segment), ready(temp.ready), exit_segment(temp.exit_segment) {
          // cout << "Called the copy constructor for the Car!" << endl;
        }

        int get_exit_segment() const;
        bool is_ready() const;
        void make_ready();

        ~Car() {

        };
};


class Entry {
    private:
        // Could also be one array, i.e. Toll** tolls;
        Toll** tolls;
        // Toll_Electronic **toll_elec;
        // Toll_Cashier **toll_cash;
        int id;
        int K;
        int no_of_tolls;
    public:
        Entry(int, int, int, int);
        void operate();
        ~Entry() {
          for(int i = 0; i < no_of_tolls; i++)
            delete tolls[i];
            
          delete[] tolls;
        }
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
        int no_of_segs;
        // list<Car> list_of_cars;

    public:
        Segment(int, int, int, int);
        ~Segment();
        // Functions to connect the pointers of the segments, after they have all been created!
        void connect_to_previous(Segment* to_prev);
        void connect_to_next(Segment* to_next);


        void enter();
        void exit();
        void pass();
        int get_no_of_vehicles();
        void operate();

        void print();

        // Test functions to iterate a segment using the pointers
        void iterate_segment();
        void iterate_segment_bw();
		    void allocate_cars(int n) { cars.reserve(n); };
        void makeRandomReady();

};


class Road {
    private:
        int N, NSegs, K, Percent; 
        Segment **segment;
        int total_cars; 
    public:
        Road(int, int, int); 
        ~Road();
        void operate();
};