#pragma once
#ifndef DOCTOR_H
#define DOCTOR_H
#include "person.h"

class Doctor :public Person {
private:
    string specialization;
    string room;
    int experience_year;
    int patients_waiting = 0;
    double price;

public:
    static long long set_id;
    void set_data(sf::RenderWindow& window, sf::Event& event, int& closeflag);
    void display() const;
    void update_info(sf::RenderWindow& window, sf::Event& event, int& closeflag);
    void update_data();
    void update_patients_waiting(const string& modify);


    void read_a_object_from_file(const string& line);
    void write_a_object_to_file(ofstream& file);

    int get_waiting() const { return patients_waiting; }
    string get_specialization()const { return specialization; }
    string get_room()const { return room; }
    double get_price()const { return price; }
    ////////////////////////////////////////////////////////////////////////////
    string toString() const {
        stringstream ss;
        ss << Person::toString() 
            << "  "
            << st(specialization, 25)
            << st(room, 7)
            << st(to_string(experience_year), 9)
            << "  "
            << st(to_string(patients_waiting), 11)
            << st(to_string(int(price)), 6)
            << "  "
            << st(password, 18)
            << st((is_deleted ? "Yes" : "No"), 8);

        return ss.str();
    }
    string setheader() const {
        stringstream ss;
        ss << Person::setheader()
            << "  "
            << st("Specialization", 25)
            << st("Room", 7)
            << st("Exp_year", 9)
            << "  "
            << st("Waiting", 11)
            << st("Price", 6)
            << "  "
            << st("Password", 18)
            << st(("Deleted"), 8);

        return ss.str();
    }

};

#endif
