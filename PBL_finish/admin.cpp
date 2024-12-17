#include "admin.h"

void Admin::read_a_object_from_file(const string& line) {
    stringstream ss(line);
    string item;

    // Read and convert id_doctor
    std::getline(ss, item, ',');
    id_admin = stoll(item);

    // Read the rest of the person's data
    std::getline(ss, password, ',');

    std::getline(ss, item, ',');
    is_deleted = (item == "1");
}

void Admin::write_a_object_to_file(ofstream& file) {
    if (file.is_open()) {
        file << id_admin << ","
            << password << ","
            << (is_deleted ? "1" : "0") << endl;
    }
    else {
        cerr << "Error: File is not open." << endl;
    }
}