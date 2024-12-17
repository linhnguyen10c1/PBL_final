#pragma once
#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H
#include <iostream>
#include <string>
#include "medicine.h"
#include "linklist.h"
using namespace std;
class Prescription {
private:
    long long ID_checking;
    long long ID_medicine;
    int quantity;
    double price;
    string instruction;
    string function;
public:

    // Hàm thiết lập dữ liệu
    void set_data(long long ID_checking, long long ID_medicine, int quantity, const string& instruction, LinkedList<Medicine>& medicine_list);

    long long get_id() const { return ID_checking; }

    long long get_id_doctor() const { return ID_medicine; } // lấy ID_medicine, phải lấy tên hàm vậy để tái sử dụng code hàm add_for_test

    // Hàm hiển thị thông tin
    void display() const;

    // Hàm đọc một đối tượng từ file
    void read_a_object_from_file(const string& line);

    // Hàm ghi một đối tượng vào file
    void write_a_object_to_file(ofstream& file);
    ////////////////////////////////////////////////////////////////////////////
    string toString() const {
        stringstream ss;
        
        return ss.str();
    }
    string setheader() const {
        stringstream ss;
        
        return ss.str();
    }

};

#endif