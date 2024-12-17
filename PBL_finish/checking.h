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

    /*ph?i xem x�t c� kh?n c?p kh�ng, v� xem danh s�ch �?i c?a b�c
    s? �? m� ph�n lu�ng ng�?i kh�m ra sao*/
    int priority = 0;
    // sau khi ph�n lu?ng s? cho th�ng tin b�c s? kh�m
    string room = "0";
    string status_checking = "waiting";// waiting, processing, completed
    string start_checking = "0";
    string end_checking = "0";

    /* n?u b�c s? l�m s�ng k?t qu? kh�m cu?i c�ng
    n?u l� b�c s? c?n l�m s�ng k?t qu? testing*/
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

    // d�nh cho ng�?i d�ng l� manager

    // ch? ��?c x�a giai �o?n �?u th�i, sau khi b�c s? ghi v�o r?i th? kh�ng ��?c x�a n?a
    void update_is_deleted();

    // ch? ��?c ph?c h?i khi b?n ghi �? h?an th�nh
    // c?n m?i ghi v�o th? ch? c� x�a lu�n, mu?n kh�m l?i
    // ch? c?n c�ch ID m?i, v? b�c s? ��?c ghi tr�?c �� s? ng�?i �?i �? kh�c
    void update_is_recovered();
    void update_start_day();
    void update_end_day();
    void update_result_by_doctor();


    // d�nh cho b�c s?
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

