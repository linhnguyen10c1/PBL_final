#pragma once
#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <random>
#include <SFML/Graphics.hpp>
#include "button.h"
#include "support.h"
using namespace std;
// Base class for common person attributes
class Person {
protected:
    long long ID;
    string name;
    string password = generate_random_password(5);
    string birthday;
    string gender;
    string address;
    string email;
    string phone;
    bool is_deleted = false;
public:

    static string generate_random_password(int length);

    void set_data(sf::RenderWindow& window, sf::Event& event);

    long long get_id() const { return ID; }
    string get_password() const { return password; }
    bool get_is_deleted() const { return is_deleted; }

    // c?p nh?t thông tin cá nhân + m?t kh?u
    void update_password();
    void update_is_deleted();
    void update_is_recovered();

    void display_for_out_person(sf::RenderWindow& window, sf::Event& event) const;
    ////////////////////////////////////////////////////////////////////////////////////////////


    string toString() const {
        stringstream ss;
        ss << st(to_string(ID), 10)
            << st(name, 20)
            << st(birthday, 11)
            << "  "
            << st(gender, 10)
            << st(address, 20)
            << st(email, 30)
            << st(phone, 11);
        return ss.str();
    }
    string setheader() const {
        stringstream ss;
        ss << st("ID", 10)
            << st("Name", 20)
            << st("Birthday", 11)
            << "  "
            << st("Gender", 10)
            << st("Address", 20)
            << st("Email", 30)
            << st("Phone", 11);
        return ss.str();
    }
};

#endif
