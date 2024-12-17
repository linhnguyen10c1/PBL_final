
#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
class Admin {
private:
    long long id_admin;
    string password;
    bool is_deleted;

public:
    bool get_is_deleted() const { return is_deleted; }
    void display() {}
    long long get_id() const { return id_admin; }
    string get_password() const { return password; }
    Admin(long long id_admin = 123, string password = "admin123", bool is_deleted = false)
        :id_admin(id_admin), password(password), is_deleted(is_deleted) {
    }
    void read_a_object_from_file(const string& line);
    void write_a_object_to_file(ofstream& file);
};


#endif