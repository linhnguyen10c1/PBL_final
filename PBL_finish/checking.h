#ifndef CHECKING_H
#define CHECKING_H
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <ctime>
#include "linklist.h"
#include "doctor.h"

using namespace std;

double get_price_of_doctor(long long ID_doctor);

void update_patients_waiting_in_list(long long ID_doctor, const string& modify, string room = "0");

class Checking {
protected:
    long long id_doctor;
    long long id_checking;

    /*ph?i xem xét có kh?n c?p không, và xem danh sách ð?i c?a bác
    s? ð? mà phân luông ngý?i khám ra sao*/
    int priority = 0;
    // sau khi phân lu?ng s? cho thông tin bác s? khám
    string room = "0";
    string status_checking = "waiting";// waiting, processing, completed
    string start_checking = "0";
    string end_checking = "0";

    /* n?u bác s? lâm sàng k?t qu? khám cu?i cùng
    n?u là bác s? c?n lâm sàng k?t qu? testing*/
    string final_result = "0";

    string doctor_note = "0";
    double cost = 0;
    bool is_deleted = false;

public:
    static int x;
    static long long set_id;
    void display() const;

    long long get_id() const { return id_checking; }
    long long get_id_doctor() const { return id_doctor; }
    string get_status_checking() const { return status_checking; }
    bool get_is_deleted() const { return is_deleted; }
    double get_cost() const { return cost; }
    string get_date() const { return start_checking; }
    int get_priority() const { return priority; }
    string get_room() const { return room; }

    // dành cho ngý?i dùng là manager

    // ch? ðý?c xóa giai ðo?n ð?u thôi, sau khi bác s? ghi vào r?i th? không ðý?c xóa n?a
    void update_is_deleted();

    // ch? ðý?c ph?c h?i khi b?n ghi ð? h?an thành
    // c?n m?i ghi vào th? ch? có xóa luôn, mu?n khám l?i
    // ch? c?n cách ID m?i, v? bác s? ðý?c ghi trý?c ðó s? ngý?i ð?i ð? khác
    void update_is_recovered();
    void update_start_day();
    void update_end_day();
    void update_result_by_doctor();


    // dành cho bác s?
    string toString() const {
        stringstream ss;
        ss << st(to_string(id_doctor), 15)
            << st(to_string(priority), 9)
            << st(room, 5)
            << st(status_checking, 16)
            << st((is_deleted ? "Yes" : "No"), 5);
        /*<< st(address, 20)
        << st(email, 30)
        << st(phone, 11)
        << st((is_deleted ? "Yes" : "No"), 5);*/
        return ss.str();
    }
    string setheader() const {
        stringstream ss;
        ss << st("ID doctor", 15)
            // << st("ID checking", 12)
            << st("Priority", 9)
            << st("Room", 5)
            << st("Satus_checking", 16)
            << st("I_de", 5);
        /*<< st("email", 30)
        << st("phone", 11)
        << st(("i_de"), 5);*/
        return ss.str();
    }

};


#endif 

