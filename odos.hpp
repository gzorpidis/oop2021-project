#include <iostream>
#include <vector>

# pragma once

class Segment;
class Entrance;

// Συγκεκριμένα, η Αττική Οδός αναπαριστάνεται από μια κλάση η οποία
class AttikiOdos {
	private:
		int segment_no;		// number of segments for the destructor
		Segment** segments;	// Εχει NSegs τμήματα, first(0) to -> last
		int no_of_cars;		// Εχει ένα πλήθος οχημάτων που κινούνται συνολικά σε αυτή
	public:
		AttikiOdos(int NSegs, int** segment_capacities, int k, int percent);
		~AttikiOdos();
		void operate();
};

class Car {
	int exit_node;
	bool ready_to_go;
	int curr_seg;	// 0-index-based (starting from 0)
	Segment* current_segment;
	
	public:
		Car(Segment* current_segment) : curr_seg(-1), current_segment(current_segment) {
			std::cout << "Created Car!" << std::endl;
		};
		~Car() { std::cout << "Destroying Car" << std::endl; };

		Car(const Car& temp) : current_segment(temp.current_segment), curr_seg(temp.curr_seg){
			std::cout << "Called copy constructor!" << std::endl;
		};
};

// Ενα τμήμα του αυτοκινητόδρομου αναπαριστάνεται από μια κλάση η οποία
class Segment {
	private:
		int K;
		int Percent;

		Entrance* seg_entr;		//΄Εχει μια είσοδο, might be a pointer
		int car_max;			// Εχει μια χωρητικότητα οχημάτων, max number of cars that can be on a Segment
		int car_on;				// Εχει ένα σύνολο οχημάτων που κινούνται σε αυτό, current counter of cars on Segment

		// Pointers to the next and previous segments
		Segment** next; // ΄Εχει (ενδεχόμενα) ένα επόμενο τμήμα
		Segment** prev;	//  Έχει (ενδεχόμενα) ένα προηγούμενο τμήμα
		std::vector<Car> cars_on;	// Εχει ένα σύνολο οχημάτων που κινούνται σε αυτό

	public:
		Segment(int max_capacity, Segment** next_seg, Segment** previous_seg, int toll_number, int k, int percent);

		int get_capacity() const { return car_max; };

		void print_capacity_prev() {
			if (prev != NULL)
				std::cout << "Capacity of previous is: " << (*prev)->get_capacity() << std::endl;
			else
				std::cout << "There is no previous!" << std::endl;
		};

		void print_capacity_next() {
			if (next != NULL)
				std::cout << "Capacity of next is: " << (*next)->get_capacity() << std::endl;
			else
				std::cout << "There is no next!" << std::endl;
		}

		void enter();
		void exit();
		void pass();
		void get_no_of_vehicles();
		void operate();
		~Segment();

		void allocate_cars(int n) { cars_on.reserve(n); };
};

class Tollbooth;

class Entrance {
		int node_id;		//  Έχει το όνομα/ταυτότητα του κόμβου
		Tollbooth** tolls;	// ΄Εχει ένα σύνολο διοδίων με υπαλλήλους, έχει ένα σύνολο ηλεκτρονικών διοδίων

	public:
	Entrance( int toll_number );
	~Entrance() { std::cout << "Destroying entrance!" << std::endl;};
	// Αϕαιρούνται οχήματα από την είσοδο, αϕαιρώντας οχήματα από τα διόδια.
	void remove_from_entrance();

	// Προστίθενται τυχαία οχήματα στα *διόδιά* της.
	void add_to_entrance();
};


// ΄Ενα διόδιο αναπαριστάνεται από το σύνολο των οχημάτων που περιμένουν να μπούν. 
// Αρχικά, δημιουργούνται τυχαία αυτοκίνητα που περιμένουν σε αυτό. (constructor)
// Προστίθενται οχήματα στο διόδιο. (add_car) Αϕαιρούνται οχήματα από το διόδιο (remove_car)

class Tollbooth {
	protected:
		std::vector<Car> cars; // Ενα διόδιο αναπαριστάνεται από το σύνολο των οχημάτων που περιμένουν να μπούν
		Entrance* toll_of_entrance;
	public:
		Tollbooth(Entrance* belongs_to_entrance) :toll_of_entrance(belongs_to_entrance) {std:: cout << "Initialized a Tollbooth" << std:: endl; };	// Creates the car vector automatically
		virtual ~Tollbooth() = default;
		// We will use inheritance, we need them to be virtual so they call the subclasses' functions
		virtual void add_car() = 0;
		virtual void remove_car() = 0;
};

// There are two types of Tollbooths, Electronic (E-Tb) and with Employees (Employee_Tb)

class E_Tb : public Tollbooth {
	public:
		E_Tb(Entrance* belongs_to_entr) : Tollbooth(belongs_to_entr) {
			std::cout << "Created a Electronic toll" << std::endl;
		};

		~E_Tb() {

		};

		void add_car() override {

		}

		void remove_car() override {

		}
};

class Employee_Tb : public Tollbooth {
	public:
		Employee_Tb(Entrance* belongs_to_entr) : Tollbooth(belongs_to_entr) {
			std::cout << "Created a Employee toll" << std::endl;
		};

		~Employee_Tb() {

		};

		void add_car() override {

		}
		
		void remove_car() override {

		}
};

