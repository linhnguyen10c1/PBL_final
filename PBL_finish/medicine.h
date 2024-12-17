#pragma once
#ifndef MEDICINE_H
#define MEDICINE_H

#include <iostream>
//#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "button.h"
#include "support.h"
using namespace std;


class Medicine
{
private:
    long long id_medicine;
    string name;
    string type;
    string usage;// công d?ng
    string dosage;// s? lý?ng dùng nhi?u nh?t trong m?t ngày
    string side_effects;// tác d?ng ph?
    string warnings;// c?nh báo
    string NSX;
    int HSD; // month
    int quantity;
    double cost;// giá ti?n trên m?t ðõn v? ð?ng thu?c
    bool is_deleted = false;

public:
    static long long set_id;
    void set_data(sf::RenderWindow& window, sf::Event& event, int& closeflag);
    void update_info(sf::RenderWindow& window, sf::Event& event, int& closeflag);
    void display() const;
    void update_data();
    void update_quantity(int x) {
        quantity += x;
    }
    void update_is_deleted();
    void update_is_recovered();

    //void decrease_quantity();// khi kê ðõn cho th? h? th?ng t? ð?ng tr? quatity trong kho
    void decrease_quantity(int x) {
        quantity -= x;
    };
    void read_a_object_from_file(const string& line);
    void write_a_object_to_file(ofstream& file);

    long long get_id() const { return id_medicine; }
    bool get_is_deleted() const { return is_deleted; }
    string get_name() const { return name; }
    int get_quantity()const { return quantity; }
    double get_price() const { return cost; }
    string get_function()const { return usage; }
    std::string toString() const {
        std::stringstream ss;
        ss << st(to_string(id_medicine), 10)
            << st(name, 17)
            << st(type, 10)
            << st(usage, 30)
            << st(dosage, 15)
            << st(side_effects, 35)
            << st(warnings, 40)
            << st(NSX, 14)
            << st(to_string(HSD), 4)
            << st(to_string(quantity), 9)
            << st(to_string(int(cost)), 5)
            << " "
            << st((is_deleted ? "Yes" : "No"), 5);
        return ss.str();
    }
    string setheader() const {
        stringstream ss;
        ss << st("ID", 10)
            << st("name", 17)
            << st("type", 10)
            << st("usage", 30)
            << st("dosage", 15)
            << st("side_effects", 35)
            << st("warnings", 40)
            << st("NSX", 14)
            << st("HSD", 4)
            << st("quantity", 9)
            << st("cost", 5)
            << " "
            << st("i_de", 5);
        return ss.str();
    }

};

#endif