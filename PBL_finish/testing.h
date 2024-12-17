#ifndef TESTING_H
#define TESTING_H

#include "linklist.h"
#include "checking.h"
#include <iostream>
#include <string>
#include "record.h"

using namespace std;

class Testing :public Checking {
private:
    long long id_doctor2 = 0;
    string type;
    string part_of_body_need_test;
    bool is_having_another_testing = true;
    double cost;
    //string imagine;

public:
    void display() const;
    void set_data(long long id_checking, const string& type, int priority, const string& part_body);
    //dùng ð? c?p nh?t k?t qu? t? bác s? c?n lâm sàn
    void update_data();

    void update_data_have_another_testing() {
        is_having_another_testing = false;
    }
    bool get_is_having_another_testing() {
        return is_having_another_testing;
    }
    long long get_id_patient();
    bool get_testing_or_not()const { return true; }
    void check_condition_doctor(const string& type);
    void read_a_object_from_file(const string& line);
    void write_a_object_to_file(ofstream& file);
    string toString() const {
        stringstream ss;
        ss << st(to_string(id_checking), 15)
            << st(to_string(id_doctor), 15)

            << st(to_string(id_doctor2), 15)
            << st(to_string(priority), 9)
            << st(room, 5)
            << st(status_checking, 16)
            << st((is_deleted ? "Yes" : "No"), 5)
            // << "Heart Rate: " << heart << ", "
            //<< "Blood Pressure: " << blood << ", "
            << st(type, 10)
            //<< st(status_patient,40)
            << st(part_of_body_need_test, 20)
            << st(to_string(cost), 10)
            << " "
            << st((is_having_another_testing ? "Yes" : "No"), 20);
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
            << st("Id doctor 1", 15)
            << st("ID doctor 2", 15)
            // << st("ID checking", 12)
            << st("Priority", 9)
            << st("Room", 5)
            << st("Satus_checking", 16)
            << st("I_de", 5)

            << st("Type", 10)
            //<< st(status_patient,40)
            << st("Test_part_of_body", 20)
            << st("Cost:", 10)
            << " "
            << st("Having another test", 20);
        //<< "Doctor Note: " << doctor_note << ", "
        //<< "Follow-up Appointment: " << follow_up_appointment << ", "
        //<< "Cost: " << cost << ", "
        //<< st((if(status_payment!=0)"Yes":"No"),16)
        //<< "Is Deleted: " << (is_deleted ? "Yes" : "No");
        return ss.str();
    }

};
#endif#pragma once
