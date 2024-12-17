#pragma once
#ifndef PATIENT_H
#define PATIENT_H
#include "person.h"
class Patient : public Person
{
private:
    string allergy;
    string phone_family;

public:
    static long long set_id;
    void set_data(sf::RenderWindow& window, sf::Event& event, int& closeflag);
    void display() const;
    void show(sf::RenderWindow& window);
    void update_info(sf::RenderWindow& window, sf::Event& event, int& closeflag);
    void update_data();
    void read_a_object_from_file(const string& line);
    void write_a_object_to_file(ofstream& file);

    std::string toString() const {
        std::stringstream ss;
        ss << Person::toString()
            << "  "
            << st(allergy, 15)
            << st(phone_family, 13)
            << "  "
            << st(password, 18)
            << st((is_deleted ? "Yes" : "No"), 8);

        return ss.str();
    }
    string setheader() const {
        stringstream ss;
        ss << Person::setheader()
            << "  "
            << st("Allergy", 15)
            << st("Family Phone", 13)
            << "  "
            << st("Password", 18)
            << st(("Deleted"), 8);

        return ss.str();
    }

};

#endif