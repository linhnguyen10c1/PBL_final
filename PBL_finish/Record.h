#pragma once
#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <ctime>
#include "checking.h"
#include "patient.h"
#include "doctor.h"
#include "linklist.h"
#include "testing.h"

#include <SFML/Graphics.hpp>
#include "button.h"

using namespace std;

//void where(long long ID_checking, LinkedList<Testing>& testing_list);
class Record :public Checking {
private:
    long long id_patient;
    double heart = 0;
    double blood = 0;
    string symptom = "0";
    string diagnosis = "0";
    string status_patient = "0";
    bool testing_or_not = false;// có th?c hi?n test hay không
    bool transfer_hospital = false;// có chuy?n vi?n hay không
    double status_payment = 0;
    string follow_up_appointment = "0";

public:
    static long long set_id;
    // dành cho administrator KHÓ
    /*1. ðýa ra ID checking t? ð?ng
      2. cho bt ai là ngý?i khám, ph?ng nào
      d?a vào ð? kh?n c?p, bác s? ðang có ngý?i ch? ít nh?t
      3. tr?ng thái waiting*/
      // void set_data(sf::RenderWindow& window, sf::Event& event, int& closeflag);
    void set_data(sf::RenderWindow& window, sf::Event& event, int& closeflag);
    void display() const;
    void update_info(sf::RenderWindow& window, sf::Event& event, int& closeflag);
    void update_data();
    long long get_id_patient() const { return id_patient; }
    bool get_testing_or_not()const { return testing_or_not; }

    // dành cho doctor_general
    //void update_data_general_doctor(double x);

    void read_a_object_from_file(const string& line);
    void write_a_object_to_file(ofstream& file);
    void testing_detail(long long ID_checking, int priority, sf::RenderWindow& window);
    string toString() const {
        stringstream ss;
        ss << st(to_string(id_checking), 15)
            << st(to_string(id_patient), 15)
            << Checking::toString()
            // << "Heart Rate: " << heart << ", "
            //<< "Blood Pressure: " << blood << ", "
            << st(diagnosis, 40)
            //<< st(status_patient,40)
            << st((testing_or_not ? "Yes" : "No"), 13)
            << st((transfer_hospital ? "Yes" : "No"), 19)
            << st(final_result, 50);
        //<< "Doctor Note: " << doctor_note << ", "
        //<< "Follow-up Appointment: " << follow_up_appointment << ", "
        //<< "Cost: " << cost << ", "
        //<< st((if(status_payment!=0)"Yes":"No"),16)
        //<< "Is Deleted: " << (is_deleted ? "Yes" : "No");
        return ss.str();
    }
    string setheader() const {
        stringstream ss;
        ss << st("Id checking", 15)
            << st("Id patient", 15)
            << Checking::setheader()
            << st("diagnosis", 40)
            //<< st(status_patient,40)
            << st("Is testing?", 13)
            << st("transfer hospital?", 19)
            << st("final_result", 50);
        //<< "Doctor Note: " << doctor_note << ", "
        //<< "Follow-up Appointment: " << follow_up_appointment << ", "
        //<< "Cost: " << cost << ", "
        //<< st((if(status_payment!=0)"Yes":"No"),16)
        //<< "Is Deleted: " << (is_deleted ? "Yes" : "No");
        return ss.str();
    }

};


#endif 

